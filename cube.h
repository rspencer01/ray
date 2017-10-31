#ifndef __CUBE_H__
#define __CUBE_H__

#include "vector3.h"
#include "object.h"

struct scene;

struct cube : public object
{
  float sideLength;
  cube(scene* _parentScene);
  bool inside(v position);
  v getNormal(v position, v nextPosition);
  bool rayIntersects(v position, v direction);
  double nextPosition(v position, v direction);
};

#endif
