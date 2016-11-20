#ifndef ATOMIC_POINTER_H
#define ATOMIC_POINTER_H

namespace zy {

//__volatile__表示阻止编译器对该值进行优化，
// 强制变量使用精确内存地址（非 cache或register），memory表示对内存有修改操作，需要重新读入

inline void MemoryBarrier() {
  __asm__ __volatile__("":: : "memory");
}

class AtomicPointer{
 private:
  void * rep_;
 public:
  AtomicPointer(){}
  explicit AtomicPointer(void * p):rep_(p){}

  inline void *NoBarried_Load() const{
    return rep_;
  }

  inline void NoBarrier_Store(void * v){
    rep_= v;
  }

  inline void * Acquare_Load() const{
    void * result = rep_;
    MemoryBarrier();
    return result;
  }

  inline void  Release_Store(void * v){
    MemoryBarrier();
    rep_ = v;
  }

};

}

#endif