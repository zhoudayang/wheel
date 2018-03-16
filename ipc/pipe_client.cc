#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct fifo_cmd
{
  pid_t pid;
  char cmd[100];
};

/// 这是一个简单的利用命名管道的通讯程序，客户端进程通过命名管道向服务端进程发送命令，
///　服务端收到这个命令，会将其打印出来
///　对于打开的命名管道，不显示unlink,　不会将其回收

int main(int argc, char *argv[])
{
  int fd;
  struct fifo_cmd cmd;
  if ((fd = open("/tmp/server", O_WRONLY)) < 0)
  {
    perror("open fail: ");
    exit(-1);
  }

  cmd.pid = getpid();

  while (true)
  {
    printf("%%: ");
    fgets(cmd.cmd, sizeof(cmd.cmd), stdin);
    cmd.cmd[strlen(cmd.cmd) - 1] = 0;
    if (write(fd, &cmd, sizeof(cmd)) < 0)
    {
      perror("write fail: ");
      exit(-1);
    }
  }
}