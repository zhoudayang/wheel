#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
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
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
  
  system("touch /tmp/shared_memory");

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
  msg->flag = 0;
  // 初始化互斥量　
  pthread_mutex_init(&msg->sm_mutex, &attr);

  bool running = true;

  while (running)
  {
    pthread_mutex_lock(&msg->sm_mutex);
    if (msg->flag == 1)
    {
      printf("read message: %s\n", msg->buf);
      msg->flag = 0;
      pthread_mutex_unlock(&msg->sm_mutex);
      if (0 == strncmp(msg->buf, "exit", 4))
      {
        running = false;
      }
    }
    else
    {
      printf("no available data to read, sleep...\n");
      pthread_mutex_unlock(&msg->sm_mutex);
      sleep(2);
    }
  }

  int ret = shmdt(shared_memory);
  if (ret < 0)
  {
    perror("failed to shmdt");
    exit(1);
  }

  if (shmctl(shm_id, IPC_RMID, 0) < 0)
  {
    perror("failed to shmctl");
    exit(-1);
  }

  return 0;
}