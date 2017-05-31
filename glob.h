#ifndef __GLOB_H__
#define __GLOB_H__

#include "vector3.h"
#include "utils.h"
#include "ray.h"
#include "material.h"
#include "object.h"
#include <vector>

struct scene;

struct glob : public object
{
  double sigma;
  std::vector<v> controls;
  glob(scene* _parentScene) : object(_parentScene)
  {
    position = v(0,0,0);
    rayRadius = 0;
    limit = 12;
    sigma = 1;
  };
  bool inside(v position);
  v getNormal(v position, v nextPosition);
  void addControl(v position);
  void setRadius(double radius);
  private:
    double getField(v);
    double limit;
};

#endif
