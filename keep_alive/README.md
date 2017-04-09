## 进程守护小工具

* 使用signal_fd 监控 SIGCHILD 信号
* 使用epoll 监控signal_fd
* 若启动的进程退出，自动重启 