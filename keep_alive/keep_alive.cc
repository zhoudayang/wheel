#include <cstdio>
#include <string.h>
#include <sys/signalfd.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/epoll.h>
#include <cstdarg>
#include <muduo/base/Logging.h>
#include <muduo/base/LogFile.h>
#include <memory>
#include <sys/wait.h>

void handle_error(const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  exit(-1);
}

std::unique_ptr<muduo::LogFile> g_logFile;

void outputFunc(const char* msg, int len)
{
  g_logFile->append(msg, len);
}

void flushFunc()
{
  g_logFile->flush();
}

void init_log()
{
  g_logFile.reset(new muduo::LogFile("/tmp/keep_alive", 512 * 1024, false, 1, 1));
  muduo::Logger::setOutput(outputFunc);
  muduo::Logger::setFlush(flushFunc);
  muduo::Logger::setLogLevel(muduo::Logger::DEBUG);
}

void fork_and_exec(const char* file, char* const args[])
{
  pid_t pid = vfork();
  if(pid == -1)
  {
    LOG_FATAL << "vfork error : " << strerror(errno);
  }
  // child process
  if(pid == 0)
  {
    if(execvp(file, args) == -1)
    {
      LOG_FATAL << "execvp error!";
    }
  }
}

int main(int argc, char* const argv[])
{
  if(argc < 2)
  {
    handle_error("Usage: %s exe_name args...\n", ::basename(argv[0]));
  }

  // create daemon process
  if(daemon(0,0) == -1)
  {
    handle_error("daemon error: %s \n", strerror(errno));
  }

  // init log operations
  init_log();

  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGCHLD);

  // block SIGCHLD signal
  if(sigprocmask(SIG_BLOCK, &mask, nullptr) == -1)
  {
    LOG_FATAL << "sigprocmask error: " << strerror(errno);
  }

  // create signalfd care about SIGCHLD sigal only
  int signal_fd = signalfd(-1, &mask, SFD_NONBLOCK | SFD_CLOEXEC);
  if(signal_fd == -1)
  {
    LOG_FATAL << "signalfd error: " << strerror(errno);
  }

  // create epoll_fd, create epoll_fd when exec
  int epoll_fd = epoll_create1(EPOLL_CLOEXEC);
  if(epoll_fd == -1)
  {
    LOG_FATAL << "epoll_create error: " << strerror(errno);
  }

  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = signal_fd;
  // epoll now care about read events from signalfd
  if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, signal_fd, &ev) == -1)
  {
    LOG_FATAL << "epoll_ctl error: " << strerror(errno);
  }

  struct signalfd_siginfo fdsi;

  char* const* exe_argv = (argv + 1);

  fork_and_exec(argv[1], exe_argv);

  for(;;)
  {
    int nfds = epoll_wait(epoll_fd, &ev, 1, -1);
    if(nfds == -1 && errno != EINTR)
    {
      LOG_FATAL << "epoll_wait error: " << strerror(errno);
    }
    else if(nfds == -1 && errno == EINTR)
    {
      LOG_ERROR << "epoll_wait get EINTR error: " << strerror(errno);
    }
    // handle SIGCHLD signal
    else if(nfds > 0)
    {
      if(ev.data.fd != signal_fd ||(!ev.events & EPOLLIN))
      {
        LOG_FATAL << "ev.data.fd " << ev.data.fd << " ev.events " << ev.events;
      }
      int size = read(signal_fd, &fdsi, sizeof(struct signalfd_siginfo));
      if(size != sizeof(struct signalfd_siginfo) && errno != EINTR)
      {
        LOG_FATAL << "signal_fd read error: " << strerror(errno);
      }
      // read correctly
      if(size == sizeof(struct signalfd_siginfo))
      {
        if(fdsi.ssi_signo != SIGCHLD)
        {
          LOG_FATAL << "error signal signo " << fdsi.ssi_signo;
        }
        LOG_INFO << "get SIGCHLD signal now !";
        bool child_terminated = false;
        int status;
        int pid;
        // 回收进程资源
        while((pid = waitpid(-1, &status, WNOHANG)) > 0)
        {
          LOG_INFO << "child process " << pid << " terminated with status_code " << WEXITSTATUS(status);
          if(WCOREDUMP(status))
          {
            LOG_INFO << "child_process " << pid << " create coredump file";
          }
          child_terminated = true;
        }
        if(child_terminated)
        {
          fork_and_exec(argv[1], exe_argv);
        }
      }
    }
  }
  return 0;
}
