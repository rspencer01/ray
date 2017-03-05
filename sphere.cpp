#include "sphere.h"
#include "scene.h"

bool sphere::intersects(v position, v nextPosition)
{
  float currentRadius2 = (position - this->position)%(position - this->position);
  float nextRadius2 = (nextPosition - this->position)%(nextPosition - this->position);
  return (currentRadius2 > this->radius * this->radius)
          and (nextRadius2 < this->radius * this->radius);
}

v sphere::getNormal(v position, v nextPosition)
{
  return !((position+nextPosition)*0.5 - this->position);
}
