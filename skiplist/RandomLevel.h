//
// Created by zhouyang on 2016/10/31.
//

#ifndef SKIPLIST_RANDOMLEVEL_H
#define SKIPLIST_RANDOMLEVEL_H

namespace zy {
class RandomLevel {
 public:
  RandomLevel(int max_level, double probability);
  double getRandomLevel();
  ~ RandomLevel() {}
 private:
  // No copying allowed
  RandomLevel(const RandomLevel &);
  void operator=(const RandomLevel &);

  /*
   * max_level - max number of levels in the skip list
   * probability_ - the probability with the skip list should generated
   */
  int max_level_;
  double probability_;
};
}

#endif //SKIPLIST_RANDOMLEVEL_H
