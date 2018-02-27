#include <string>
#include <sstream>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void error_handler(const char *str)
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
    fprintf(stderr, "inet_pton error\n");
    exit(-1);
  }

  if (-1 == connect(sockfd, reinterpret_cast<const struct sockaddr *>(&addr), static_cast<socklen_t>(sizeof(addr))))
  {
    error_handler("connect to server error!\n");
  }

  std::stringstream ss;

  for (int i = 1; i < 10; ++i)
  {
    for (int j = 1; j < 10; ++j)
    {
      ss << i * j << " ";
    }
    ss << std::endl;
  }

  auto result = ss.str();

  if (write(sockfd, static_cast<const void *>(result.c_str()), result.size()) == -1)
  {
    error_handler("send result to server error!");
  }

  if (-1 == shutdown(sockfd, SHUT_WR))
  {
    error_handler("shutdown error\n");
  }

  int len;
  size_t LEN = 8;
  char buff[LEN];

  if ((len = read(sockfd, static_cast<void *>(buff), LEN)) == 0)
  {
    std::cout << "remote server close the connection, terminate the program!" << std::endl;
    close(sockfd);
  }
  else if (len == -1)
  {
    error_handler("read error\n");
  }
  else
  {
    fprintf(stderr, "read invalid data from server!\n");
    exit(-1);
  }

  return 0;
}