#ifndef SINGLETON_H
#define SINGLETON_H

#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

namespace zy
{

template<typename T>
struct has_no_destroy
{
#if __cplusplus > 199711L
  template<typename C> static char test(decltype(&C::nodestroy));
#else
  template<typename C> static char test(typeof(&C::nodestroy));
#endif
  template<typename C> static int32_t test(...);

  static const bool value = sizeof(test<T>(0)) == 1 ? 1 : 0;
};


template<typename T>
class Singleton
{
public:
  static T * instance()
  {
    pthread_once(&ponce_, Singleton::init);
    assert(value_ != NULL);
    return value_;
  }

private:
  Singleton(const Singleton &);
  void operator = (const Singleton &);

  static void init()
  {
    value_ = new T();
    if(!has_no_destroy<T>::value)
    {
      ::atexit(&Singleton::destroy);
    }
  }

  static void destroy()
  {
    typedef char T_must_be_complete_type [sizeof(T) == 0 ? -1 : 1];
    T_must_be_complete_type dummy; (void) dummy;
    delete value_;
    value_ = NULL;
  }
  static pthread_once_t ponce_;
  static T*             value_;
};

template<typename T>
pthread_once_t Singleton<T> :: ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T> :: value_ = NULL;

}
#endif
