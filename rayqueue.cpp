#include <algorithm>
#include "rayqueue.h"

void rayqueue::add(ray* ry)
{
  elements.push_back(ry);
}

ray* rayqueue::remove()
{
  mutex.lock();
  ray* ans = elements.back();
  elements.pop_back();
  mutex.unlock();
  return ans;
}

bool rayqueue::empty()
{
  return elements.empty();
}

void rayqueue::shuffle()
{
  std::random_shuffle(elements.begin(), elements.end());
}
