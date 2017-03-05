#ifndef __OBJECT_H__
#define __OBJECT_H__

struct scene;

struct object
{
  v position;
  float rayRadius;
  scene* parentScene;
  object(scene* _parentScene);
  virtual voxel intersects(v position, v nextPosition, v direction, ray& callingRay);
};

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
#endif
