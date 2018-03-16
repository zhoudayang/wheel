#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>

#define BUF_SIZE 1024

struct msg_st
{
  long msg_type;
  char text[BUF_SIZE];
};

int main()
{
  int running = 1;
  int msgid = -1;
  struct msg_st data;

  long msgtype = 0;

  // 创建消息队列　
  msgid = msgget((key_t) 1234, 0666 | IPC_CREAT);
  if (msgid == -1)
  {
    fprintf(stderr, "msgget failed with error: %d\n", errno);
    exit(-1);
  }

  while (running)
  {
    if (msgrcv(msgid, (void *) &data, BUFSIZ, msgtype, 0) == -1)
    {
      fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
      exit(-1);
    }
    printf("you wrote: %s\n", data.text);
    /// 遇到end 退出
    if (strncmp(data.text, "end", 3) == 0)
    {
      running = 0;
    }
  }

  if (msgctl(msgid, IPC_RMID, 0) == -1)
  {
    fprintf(stderr, "msgctl(IPC_RMID) failed\n");
    exit(-1);
  }
  return 0;
}
