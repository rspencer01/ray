#include "sphere.h"
#include "scene.h"

voxel sphere::intersects(v position, v nextPosition, v direction, ray& callingRay)
{
  float currentRadius2 = (position - this->position)%(position - this->position);
  float nextRadius2 = (nextPosition - this->position)%(nextPosition - this->position);
  v norm = !(position - this->position);
  if ((currentRadius2 > this->radius * this->radius)
    and (nextRadius2 < this->radius * this->radius))
  {
    return this->mat.getInteraction(position, norm, direction, callingRay, parentScene);
  }
  return voxel();
}
