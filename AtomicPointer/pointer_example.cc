#include <cstdio>
#include <unistd.h>
#include <thread>
#include <mutex>
#include "AtomicPointer.hpp"

using namespace zy;


//AtomicPointer可以用于多消费者单生产者的应用，下面是一个简单的示例程序
class Number {
 public:
  Number(int value) {
    setNumber(static_cast<intptr_t>(value));
  }

  void setNum(int value) {
    setNumber(static_cast<intptr_t>(value));
  }

  int getNum() const {
    return static_cast<int>(GetNumber());
  }

 private:
  intptr_t GetNumber() const {
    return reinterpret_cast<intptr_t>(number_.Acquare_Load());
  }

  void setNumber(intptr_t v) {
    number_.Release_Store(reinterpret_cast<void *>(v));
  }

  AtomicPointer number_;
};

Number num(0);

void writer() {
  for (int i = 1; i <= 5; ++i) {
    printf("I change the num to %d\n!", i);
    sleep(1);
    num.setNum(i);
  }
}

void reader() {
  while (true) {
    int value = num.getNum();
    printf("I get the number, is %d \n", value);
    if (value == 5)
      break;
  }
}

int main() {

  std::thread reader1(reader);
  std::thread reader2(reader);
  std::thread write(writer);

  reader1.join();
  reader2.join();
  write.join();

}