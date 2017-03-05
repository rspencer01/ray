#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "vector3.h"
#include "ray.h"
#include "material.h"

struct scene;

struct object
{
  v position;
  float rayRadius;
  scene* parentScene;
  material mat;
  object(scene* _parentScene);
  virtual voxel intersects(v position, v nextPosition, v direction, ray& callingRay);
  virtual bool intersects(v position, v nextPosition);
  virtual v getNormal(v position, v nextPosition);
};

#endif
