#include "cube.h"

cube::cube(scene* _parentScene) : object(_parentScene)
{
  parentScene = _parentScene;
  position = v(2*R()-1,2*R()-1,R()+1);
  sideLength = R()/2;
  rayRadius = sideLength*1.5;
}

bool cube::inside(v position)
{
  return (-sideLength/2 <= position.x - this->position.x and
           sideLength/2 >  position.x - this->position.x and
          -sideLength/2 <= position.y - this->position.y and
           sideLength/2 >  position.y - this->position.y and
          -sideLength/2 <= position.z - this->position.z and
           sideLength/2 >  position.z - this->position.z);
}

v cube::getNormal(v position, v nextPosition)
{
  if (position.x - this->position.x < -sideLength/2)
    return v(-1,0,0);
  if (position.x - this->position.x >  sideLength/2)
    return v( 1,0,0);
  if (position.y - this->position.y < -sideLength/2)
    return v(0,-1,0);
  if (position.y - this->position.y >  sideLength/2)
    return v(0, 1,0);
  if (position.z - this->position.z < -sideLength/2)
    return v(0,0,-1);
  if (position.z - this->position.z >  sideLength/2)
    return v(0,0, 1);
}
