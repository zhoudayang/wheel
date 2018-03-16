# ipc通讯demo

## 管道
### pipe1
未名管道之hello_world实现

### pipe_client and pipe_server
这是一个简单的利用命名管道的通讯程序，客户端进程通过命名管道向服务端进程发送命令，服务端收到这个命令，会将其打印出来。对于打开的命名管道，不unlink,　不会将其回收

## 消息队列
###  msg_sender and msg_receiver
这是一个简单的利用消息队列的通讯程序，sender从stdin中读取数据，发送到receiver, 二者遇到end退出。　打开的消息管道，如果不显示remove,　操作系统不会将其回收

## 信号量
### semaphore
父子进程之间通过信号量进行同步，保证输出的front字符和second字符总是成对出现。打开的信号量，如果不显示删除，操作系统不会将其回收

## 共享内存
### shm_sender shm_receiver
两个进程之间通过共享内存进行通信，通过存储于共享内存的`pthread_mutex_t`进行同步互斥。sender取得锁之后，将信息发送给receiver, receiver在读取的过程中也要持有锁。 如果不显示remove, 操作系统不会将共享内存回收　