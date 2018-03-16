#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUF_SIZE 1024

struct sm_msg
{
  int flag;
  pthread_mutex_t sm_mutex;
  char buf[BUF_SIZE];
};

int main()
{
  key_t key = ftok("/tmp/shared_memory", 1);
  int shm_id = shmget(key, sizeof(struct sm_msg), 0666 | IPC_CREAT);
  if (shm_id < 0)
  {
    perror("shmget failed!");
    exit(-1);
  }

  void *shared_memory = shmat(shm_id, NULL, 0);
  if (shared_memory == NULL)
  {
    perror("failed to shmat");
    exit(-1);
  }

  struct sm_msg *msg = (struct sm_msg *) shared_memory;

  bool running = true;

  while (running)
  {
    printf("wait lock\n");
    pthread_mutex_lock(&msg->sm_mutex);
    printf("get lock\n");
    if (msg->flag == 1)
    {
      printf("wait for other process to read\n");
      pthread_mutex_unlock(&msg->sm_mutex);
      sleep(2);
    }
    else
    {
      printf("please input data\n");
      char buf[BUF_SIZE];
      fgets(buf, BUF_SIZE, stdin);
      printf("write msg: %s\n", buf);
      strncpy(msg->buf, buf, sizeof(buf));
      msg->flag = 1;
      if (strncmp(msg->buf, "exit", 4) == 0)
      {
        running = false;
      }
      pthread_mutex_unlock(&msg->sm_mutex);
    }
  }

  int ret = shmdt(shared_memory);
  if (ret < 0)
  {
    perror("fail to shmdt");
    exit(-1);
  }

  return 0;
}