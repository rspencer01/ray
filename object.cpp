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
  return false;
}

v object::getNormal(v position, v nextPosition)
{
  return v();
}
