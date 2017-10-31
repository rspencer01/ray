#include "object.h"

object::object(scene* _parentScene)
{
  parentScene = _parentScene;
  position = v(0,0,0);
  rayRadius = 0;
}

voxel object::intersects(v position, v nextPosition, v direction, ray& callingRay)
{
  if (!intersects(position, nextPosition))
    return voxel();
  v normal = getNormal(position, nextPosition);
  return mat.getInteraction(position, normal, direction, callingRay, parentScene);
}

bool object::intersects(v position, v nextPosition)
{
  return not inside(position) and inside(nextPosition);
}

v object::getNormal(v position, v nextPosition)
{
  return v();
}

bool object::inside(v position)
{
  return false;
}

bool object::rayIntersects(v position, v direction)
{
  if (inside(position))
    return true;
  return intersectSphere(this->position,
                         this->rayRadius,
                         position,
                         direction);
}

double object::nextPosition(v position, v direction)
{
  return intersectSphereDist(this->position,
                             this->rayRadius,
                             position,
                             direction);
}
