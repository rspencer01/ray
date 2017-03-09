#include "sphere.h"

bool sphere::inside(v position)
{
  return norm(position - this->position) < this->radius;
}

v sphere::getNormal(v position, v nextPosition)
{
  return !((position+nextPosition)*0.5 - this->position);
}
