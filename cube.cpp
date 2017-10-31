#include "cube.h"

#define MIN(_a,_b) (_a)<(_b)?(_a):(_b)

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


bool cube::rayIntersects(v position, v direction)
{
  if (inside(position))
    return true;
  position = position - this->position;
  v p2 = position;
  p2 = p2 + direction * (-position.y + sideLength/2) * (1./direction.y);
  if (inside(p2*0.99 + this->position))
    return true;
  p2 = position;
  p2 = p2 + direction * (-position.y - sideLength/2) * (1./direction.y);
  if (inside(p2*0.99 + this->position))
    return true;
  p2 = position;
  p2 = p2 + direction * (-position.x - sideLength/2) * (1./direction.x);
  if (inside(p2*0.99 + this->position))
    return true;
  p2 = position;
  p2 = p2 + direction * (-position.x + sideLength/2) * (1./direction.x);
  if (inside(p2*0.99 + this->position))
    return true;
  p2 = position;
  p2 = p2 + direction * (-position.z - sideLength/2) * (1./direction.z);
  if (inside(p2*0.99 + this->position))
    return true;
  p2 = position;
  p2 = p2 + direction * (-position.z + sideLength/2) * (1./direction.z);
  if (inside(p2*0.99 + this->position))
    return true;
}

double cube::nextPosition(v position, v direction)
{
  double ans = 1000;
  position = position - this->position;
  if (direction.y != 0)
  {
    v p2 = position;
    p2 = p2 + direction * (-position.y - sideLength/2) * (1./direction.y);
    ans = MIN(ans, norm(position-p2));
    p2 = position;
    p2 = p2 + direction * (-position.y + sideLength/2) * (1./direction.y);
    ans = MIN(ans, norm(position-p2));
  }
  if (direction.x != 0)
  {
    v p2 = position;
    p2 = position;
    p2 = p2 + direction * (-position.x - sideLength/2) * (1./direction.x);
    ans = MIN(ans, norm(position-p2));
    p2 = position;
    p2 = p2 + direction * (-position.x + sideLength/2) * (1./direction.x);
    ans = MIN(ans, norm(position-p2));
  }
  if (direction.z != 0)
  {
    v p2 = position;
    p2 = position;
    p2 = p2 + direction * (-position.z - sideLength/2) * (1./direction.z);
    ans = MIN(ans, norm(position-p2));
    p2 = position;
    p2 = p2 + direction * (-position.z + sideLength/2) * (1./direction.z);
    ans = MIN(ans, norm(position-p2));
  }
  return ans;
}
