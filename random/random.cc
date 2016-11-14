#include "random.h"

using namespace zy;

///算法核心： seed = (seed * A + C) % M ,　使用线性同余法来计算下一个随机数
///当 C 为０的时候，称为"乘同余法", 下面的随机数生成器使用的就是乘同余法

//0x7fffffff == 2147483647L == 2^31-1 == 0111 1111 1111 1111 1111 1111 1111 1111
//s&0x7fffffff make sure seed is between from 0 to 2147483647L
Random::Random(uint32_t s) : seed_(s & 0x7fffffff) {
  //Avoid bad seeds
  if (seed_==0 || seed_==2147483647L) {
    seed_ = 1;
  }
}

//return next random number
uint32_t Random::Next() {
  static const uint32_t M = 2147483647L;  // 2^31 -1
  static const uint64_t A = 16807;        // 0100 0001 1010 0111
  /*
   * We are computing
   *  seed_ = (seed_ * A) % M , where M = 2^31 -1
   *  seed_ must not be zero or M, or else all subsequent computed values
   *  will be zero or M respectively. For all other values, seed_ will end
   *  up cycling through every number in [1,M-1]
   */
  uint64_t product = seed_*A;
  //compute (product % M) using the fact that ((x<<31) %M) == x
  seed_ = static_cast<uint32_t>((product >> 31) + (product & M));
  //the first reduction may overflow by 1 bit, so we may need to
  //repeat. mod == M is not possible; using > allows the faster
  //sign-bit-based test
  if (seed_ > M) {
    seed_ -= M;
  }
  return seed_;
}

//return a uniformly distributed value in the range [0..n-1]
//Requires: n > 0
uint32_t Random::Uniform(int n) {
  return Next()%n;
}

//Randomly returns true ~"1/n" of the time, and false otherwise
//Requires: n > 0
bool Random::OneIn(int n) {
  return (Next()%n)==0;
}

//pick "base" uniformly from range[0,max_log] and then
//return "base" random bits. The effect is to pick a number in the
//range [0,2^max_log-1] with exponential bias towards smaller numbers
uint32_t Random::Skewed(int max_log) {
  return Uniform(1 << Uniform(max_log + 1));
}

/*
  证明: 等式(product%M) == (product>>31)+(product&M)成立。注：M等于2^31-1。
  证明：
    因为product类型是uint64_t，可以将product的二进制从左到右分解成高33位和低31位，假设高33位的值为H，低31位的值为L，
    则product相当于高33位向左移动了31位加上低31位，即H<<31+L。
    则product等于H*2^31+L。由源码知道product=seed_*A，而seed_和A都小于M，则 ** H肯定小于M ** 。
    从而我们可以得到：
    表达式左边product%M = (H*2^31+L)%M = (H*M+H+L)%M = H+L。
    表达式右边(product>>31) + (product&M) = (H*2^31 +L)>>31+L = (H*2^31+L)/2^31+L = H+L。
    注：低31位的值L可能等于M，那么表达式左边就等于H了，此时表达式右边等于H+M,所以就有Next()代码中最后判断H是否大于M,若
    大于M就减去M。
 */