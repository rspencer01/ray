#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <math.h>
struct vector3
{
  double x,y,z;
  vector3();
  vector3(double a,double b,double c);
  vector3 operator+(vector3 r);
  vector3 operator-(vector3 r);
  vector3 operator*(double r);
  vector3 operator*(vector3 r);
  vector3 operator&(vector3 r);
  // Dot product
  double operator%(vector3 r);
  // Cross product
  vector3 operator^(vector3 r);
  // Normalise
  vector3 operator!();
};

typedef vector3 v;

double norm(vector3);

#endif
