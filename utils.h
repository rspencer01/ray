#ifndef __UTILS_H__
#define __UTILS_H__
typedef int i;
typedef double f;
#define posmod(_a,_b) (((_b)+((_a)%(_b)))%(_b))

#include "vector3.h"

v mirror(v dir,v norm);
v refract(v dir, v normal, float index);

double clamp(double a, double min, double max);

double R();

v calculateDirection(double x, double y);

double intersectSphereDist(v center, double R, v start, v direction);
bool intersectSphere(v center, double R, v start, v direction);
#endif
