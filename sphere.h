#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "vector3.h"
#include "utils.h"
#include "ray.h"
#include "material.h"
#include "object.h"

struct scene;

struct sphere : public object
{
  float radius;
  material mat;
  sphere(scene* _parentScene) : object(_parentScene)
  {
    parentScene = _parentScene;
    position = v(2*R()-1,2*R()-1,R()+1);
    radius = R()/6;
    rayRadius = radius*1.01;
  };
  voxel intersects(v position, v nextPosition, v direction, ray& callingRay);
};

#endif
