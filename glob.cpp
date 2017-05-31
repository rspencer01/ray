#include "glob.h"
#include <stdio.h>

double glob::getField(v position)
{
  double ans = 0;
  for (v control : controls)
  {
    ans += exp(-((position-control)%(position-control)*sigma));
  }
  return ans;
}

bool glob::inside(v position)
{
  return getField(position) > limit;
}

v glob::getNormal(v position, v nextPosition)
{
  double e = 0.01;
  return !v(-(getField(position+v(e,0,0))-getField(position))/e,
            -(getField(position+v(0,e,0))-getField(position))/e,
            -(getField(position+v(0,0,e))-getField(position))/e);
}

void glob::addControl(v position)
{
  controls.push_back(position);
  rayRadius = std::max(rayRadius, norm(position)+.5);
}

void glob::setRadius(double radius)
{
  limit = exp(-radius*radius*sigma);
}
