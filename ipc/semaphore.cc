#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

union semun
{
  int val;
  struct semid_ds *buf;
  unsigned short *arry;
};

static int sem_id = 0;
static int set_semvalue()
{
  union semun sem_union;
  sem_union.val = 1;
  if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
  {
    return 0;
  }
  return 1;
}

static void del_semvalue()
{
  union semun sem_union;
  if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
  {
    fprintf(stderr, "failed to delete semaphore\n");
  }
}

static int semaphore_p()
{
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = -1;
  sem_b.sem_flg = SEM_UNDO;
  if (semop(sem_id, &sem_b, 1) == -1)
  {
    fprintf(stderr, "semphore_p failed\n");
    return 0;
  }
  return 1;
}

static int semaphore_v()
{
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = 1;
  sem_b.sem_flg = SEM_UNDO;
  if (semop(sem_id, &sem_b, 1) == -1)
  {
    fprintf(stderr, "semphore_v failed\n");
    return 0;
  }
  return 1;
}

int main(int argc, char *argv[])
{
  int i = 0;
  sem_id = semget((key_t) 1234, 1, 0666 | IPC_CREAT);

  char front = 'Z';
  char second = 'X';

  if (!set_semvalue())
  {
    fprintf(stderr, "failed to initialize semaphore\n");
    exit(-1);
  }

  // 保证两个进程都是成对输出

  pid_t pid = fork();

  for (i = 0; i < 5; ++i)
  {
    if (!semaphore_p())
    {
      exit(-1);
    }
    printf("%c", front);
    fflush(stdout);
    sleep(rand() % 2);
    printf("%c", second);
    fflush(stdout);
    if (!semaphore_v())
    {
      exit(-1);
    }
    sleep(rand() % 2);
  }

  sleep(10);
  printf("\n%d - finished\n", getpid());

  if (pid > 0)
  {
    int status;
    wait(&status);
    printf("parent process terminate now!\n");
    del_semvalue();
  }

  return 0;
}
