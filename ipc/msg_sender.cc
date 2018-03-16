#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 1024

struct msg_st
{
  long msg_type;
  char text[BUF_SIZE];
};

int main()
{
  int running = 1;
  struct msg_st data;
  char buffer[BUF_SIZE];
  int msgid = -1;
  msgid = msgget((key_t) 1234, 0666 | IPC_CREAT);
  if (msgid == -1)
  {
    fprintf(stderr, "msgget failed with error: %d\n", errno);
    exit(-1);
  }

  while (running)
  {
    printf("Enter some text: ");
    fgets(buffer, BUFSIZ, stdin);
    data.msg_type = 1;
    strcpy(data.text, buffer);
    if (msgsnd(msgid, (void *) &data, BUF_SIZE, 0) == -1)
    {
      fprintf(stderr, "msgsnd failed\n");
      exit(-1);
    }
    if (strncmp(buffer, "end", 3) == 0)
    {
      running = 0;
    }
    sleep(1);
  }
  return 0;
}
