#include <string>
#include <vector>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

void error_handler(const char* str)
{
  perror(str);
  exit(-1);
}

int main()
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    error_handler("create socket error\n");
  }

  std::string ip = "127.0.0.1";
  uint16_t port = 8899;

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  if (1 != inet_pton(AF_INET, ip.c_str(), static_cast<void *>(&addr.sin_addr)))
  {
    error_handler("inet_pton error\n");
  }

  if (-1 == bind(sockfd, reinterpret_cast<const sockaddr *>(&addr), static_cast<socklen_t>(sizeof(addr))))
  {
    error_handler("bind to specified address error\n");
  }

  if (-1 == listen(sockfd, SOMAXCONN))
  {
    error_handler("listen error");
  }

  std::vector<char> buff;
  size_t LEN = 4096;
  buff.resize(LEN);

  // 迭代式服务器
  while(true)
  {
    struct sockaddr_in client_addr;
    socklen_t addr_len;
    int fd;
    if((fd = accept(sockfd, reinterpret_cast<sockaddr*>(&client_addr), &addr_len)) == -1)
    {
      error_handler("accept error\n");
    }

    while(true)
    {
      int size = read(fd, reinterpret_cast<void*>(buff.data()), LEN);
      if(size == -1)
      {
        error_handler("read error\n");
      }
      else if(size == 0)
      {
        close(fd);
        break;
      }
      else
      {
        std::string result(buff.begin(), buff.begin() + size);
        std::cout << result << std::endl;
      }
    }
  }

  return 0;
}