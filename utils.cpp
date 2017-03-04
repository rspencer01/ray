#include <stdlib.h>
#include <math.h>
#include "utils.h"

v mirror(v dir,v norm)
{
  v t = norm * ((!dir)%(norm));
  return t + t-dir;
}

float clamp(float a, float min, float max)
{
  return a<min?min:(a>max?max:a);
}

float R()
{
  return(float)rand()/RAND_MAX;
}

v calculateDirection(float x, float y)
{
  return !(v(x-.5,y-.5,1));
}

bool intersectSphere(v center, float R, v start, v direction)
{
  direction = !direction;
  v v0 = start-center;
  float c = (v0%v0) - R*R;
  float b = v0 % direction * 2;
  return (b*b > 4*c) && (-b-sqrt(b*b-4*c) > 0);
}

float intersectSphereDist(v center, float R, v start, v direction)
{
  direction = !direction;
  v v0 = start-center;
  float c = (v0%v0) - R*R;
  float b = v0 % direction * 2;
  float lambda = (-b-sqrt(b*b-4*c))/2;
  return lambda;
}
