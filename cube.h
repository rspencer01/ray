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
  bool intersects(v position, v nextPosition);
  v getNormal(v position, v nextPosition);
};

#endif
