#include "vector3.h"
#include <math.h>

vector3::vector3(){}

vector3::vector3(float a,float b,float c)
{
  x=a;
  y=b;
  z=c;
}

vector3 vector3::operator+(vector3 r)
{
  return v(x+r.x, y+r.y, z+r.z);
}

vector3 vector3::operator-(vector3 r)
{
  return v(x-r.x, y-r.y, z-r.z);
}

vector3 vector3::operator*(float r)
{
  return v(x*r, y*r, z*r);
}

vector3 vector3::operator*(vector3 r)
{
  return v(x*r.x, y*r.y, z*r.z);
}

vector3 vector3::operator&(vector3 r)
{
  return v(x*r.x, y*r.y, z*r.z);
}

// Dot product
float vector3::operator%(vector3 r)
{
  return x*r.x + y*r.y + z*r.z;
}

// Cross product
vector3 vector3::operator^(vector3 r)
{
  return v(y*r.z-z*r.y, z*r.x-x*r.z, x*r.y-y*r.x);
}

// Normalise
vector3 vector3::operator!()
{
  return *this*(1/sqrt(*this%*this));
}
