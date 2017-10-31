#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "vector3.h"
#include "ray.h"
#include "material.h"

struct scene;

struct object
{
  v position;
  double rayRadius;
  scene* parentScene;
  material mat;
  object(scene* _parentScene);
  virtual double nextPosition(v position, v direction);
  virtual bool rayIntersects(v position, v direction);
  virtual voxel intersects(v position, v nextPosition, v direction, ray& callingRay);
  virtual bool inside(v position);
  virtual bool intersects(v position, v nextPosition);
  virtual v getNormal(v position, v nextPosition);
};

#endif
