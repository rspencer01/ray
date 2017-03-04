#ifndef __UTILS_H__
#define __UTILS_H__
typedef int i;
typedef float f;
#define max(_a,_b) ((_a)>(_b)?(_a):(_b))
#define min(_a,_b) ((_a)<(_b)?(_a):(_b))
#define posmod(_a,_b) (((_b)+((_a)%(_b)))%(_b))

#include "vector3.h"

v mirror(v dir,v norm);

float clamp(float a, float min, float max);

float R();

v calculateDirection(float x, float y);

float intersectSphereDist(v center, float R, v start, v direction);
bool intersectSphere(v center, float R, v start, v direction);
#endif
