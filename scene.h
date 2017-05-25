#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "vector3.h"
#include "object.h"

struct scene
{
  int width, height;
  v sundir;
  std::vector<object*> objects;
  float ambient;
  scene();
  v boundryColour(v position, v direction);
  void loadFromFile(const char*);
};

#endif
