#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>

namespace zy {
/*
 * A very simple random number generator.
 */
class Random {
 public:
  explicit Random(uint32_t s);

  uint32_t Next();

  uint32_t Uniform(int n);

  bool OneIn(int n);

  uint32_t Skewed(int max_log);

 private:
  uint32_t seed_;
};
}

#endif
