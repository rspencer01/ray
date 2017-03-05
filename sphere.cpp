#include "sphere.h"
#include "scene.h"

bool sphere::intersects(v position, v nextPosition)
{
  float currentRadius = norm(position - this->position);
  float nextRadius = norm(nextPosition - this->position);
  return (currentRadius > this->radius)
          and (nextRadius < this->radius);
}

v sphere::getNormal(v position, v nextPosition)
{
  return !((position+nextPosition)*0.5 - this->position);
}
