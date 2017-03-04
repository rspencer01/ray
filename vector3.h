#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <math.h>

struct v
{
  float x,y,z;
  v operator+(v r)
  {
    return v(x+r.x, y+r.y, z+r.z);
  }
  v operator-(v r)
  {
    return v(x-r.x, y-r.y, z-r.z);
  }
  v operator*(float r)
  {
    return v(x*r, y*r, z*r);
  }
  v operator*(v r)
  {
    return v(x*r.x, y*r.y, z*r.z);
  }
  v operator&(v r)
  {
    return v(x*r.x, y*r.y, z*r.z);
  }

  // Dot product
  float operator%(v r)
  {
    return x*r.x + y*r.y + z*r.z;
  }
  v(){}
  // Cross product
  v operator^(v r)
  {
    return v(y*r.z-z*r.y, z*r.x-x*r.z, x*r.y-y*r.x);
  }
  v(float a,float b,float c)
  {
    x=a;
    y=b;
    z=c;
  }
  // Normalise
  v operator!()
  {
    return *this*(1/sqrt(*this%*this));
  }
};

#endif
