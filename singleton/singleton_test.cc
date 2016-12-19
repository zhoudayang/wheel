#include <iostream>
#include "singleton.h"

using namespace std;
class Instance
{
public:
  Instance()
  {
    increase();
  }

  void print()
  {
    cout<<"this is the Instance class with static value "<<value_<<endl;
  }

  ~Instance()
  {
    cout<<"the " << value_ <<"th Instance destroyed!"<<endl;
  }
private:

  static void increase()
  {
    ++ value_;
  }
  static int value_;
};

int Instance::value_ = 0;

int main()
{

  Instance * ptr1 = zy::Singleton<Instance>::instance();
  ptr1->print();

  Instance * ptr2 = zy::Singleton<Instance>::instance();
  ptr2->print();

  return 0;
}

