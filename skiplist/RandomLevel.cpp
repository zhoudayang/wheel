//
// Created by zhouyang on 2016/10/31.
//

#include "RandomLevel.h"
#include <cstdlib>
#include <ctime>

using namespace zy;

RandomLevel::RandomLevel(int max_level, double probability)
    : max_level_(max_level), probability_(probability) {
  srand(time(nullptr));
}

double RandomLevel::getRandomLevel() {
  int level = 0;
  double temp;
  while (level < max_level_) {
    temp = (double) rand() / RAND_MAX;
    if (temp > probability_)
      break;
    ++level;
  }
  return level;
}