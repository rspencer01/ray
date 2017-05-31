#include <stdlib.h>
#include <math.h>
#include "utils.h"

v mirror(v dir,v norm)
{
  v t = norm * ((!dir)%(norm));
  return t + t-dir;
}

v refract(v dir, v normal, float index)
{
  dir = dir*(-1/(dir%normal));
  v q = (normal - dir) * index;
  v ans =!((normal*-1) + q) ;
  dir = !dir;
  if (ans % normal < 0)
    return !dir * -1;
  return ans * -1;
}

double clamp(double a, double min, double max)
{
  return a<min?min:(a>max?max:a);
}

double R()
{
  return(double)rand()/RAND_MAX;
}

v calculateDirection(double x, double y)
{
  return !(v(x-.5,y-.5,1));
}

bool intersectSphere(v center, double R, v start, v direction)
{
  direction = !direction;
  v v0 = start-center;
  double c = (v0%v0) - R*R;
  double b = v0 % direction * 2;
  return (b*b >= 4*c) && (-b-sqrtl(b*b-4*c) >= 0);
}

double intersectSphereDist(v center, double R, v start, v direction)
{
  direction = !direction;
  v v0 = start-center;
  double c = (v0%v0) - R*R;
  double b = v0 % direction * 2;
  double lambda = (-b-sqrtl(b*b-4*c))/2;
  return lambda;
}
