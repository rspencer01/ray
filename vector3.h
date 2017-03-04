#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <math.h>
struct vector3
{
  float x,y,z;
  vector3();
  vector3(float a,float b,float c);
  vector3 operator+(vector3 r);
  vector3 operator-(vector3 r);
  vector3 operator*(float r);
  vector3 operator*(vector3 r);
  vector3 operator&(vector3 r);
  // Dot product
  float operator%(vector3 r);
  // Cross product
  vector3 operator^(vector3 r);
  // Normalise
  vector3 operator!();
};

typedef vector3 v;

#endif
