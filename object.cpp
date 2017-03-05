#include "object.h"

object::object(scene* _parentScene)
{
  parentScene = _parentScene;
  position = v(0,0,0);
  rayRadius = 0;
}

voxel object::intersects(v position, v nextPosition, v direction, ray& callingRay)
{
  return voxel();
}
