#ifndef __RAY_QUEUE__
#define __RAY_QUEUE__

#include <vector>
#include <mutex>
#include "ray.h"

struct rayqueue
{
  std::vector<ray*> elements;
  void add(ray*);
  ray* remove();
  void shuffle();
  bool empty();
  int size();
  private:
    std::mutex mutex;
};

#endif
