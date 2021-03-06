#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct fifo_cmd
{
  pid_t child_pid;
  char cmd[100];
};

int main()
{
  int fd;
  struct fifo_cmd cmd;
  int err;
  int n;
  if ((err = mkfifo("/tmp/server", 0777)) < 0)
  {
    if (errno != EEXIST)
    {
      perror("mkfifo fail: ");
      exit(-1);
    }
  }

  if ((fd = open("/tmp/server", O_RDONLY)) < 0)
  {
    perror("open fail: ");
    exit(-1);
  }

  while(true)
  {
    if((n = read(fd, &cmd, sizeof(cmd))) < 0)
    {
      perror("read fail: ");
      exit(-1);
    }
    if(n > 0)
    {
      printf("command from %d: %s\n", cmd.child_pid, cmd.cmd);
    }
    sleep(1);
  }

  return 0;
}