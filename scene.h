#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "vector3.h"
#include "sphere.h"

#define NUM_SPHERES 10

struct scene
{
  v sundir;
  std::vector<sphere> spheres;
  float ambient;
  scene()
  {
    ambient = 0.1;
    sundir = !v(1.3,1,-0.4);
    for (int i = 0; i< NUM_SPHERES;++i)
      spheres.push_back(sphere(this));
    spheres[0].position = v(.8,0,2);
    spheres[0].radius = 0.5;
    spheres[0].rayRadius = 0.505;
    spheres[0].mat.color = v(0,0.1,0);
    spheres[0].mat.reflectivity = 0.13;
    spheres[1].position = v(-.8,-.1,2.05);
    spheres[1].radius = 0.5;
    spheres[1].rayRadius = 0.505;
    spheres[1].mat.color = v(0,0,0.1);
    spheres[1].mat.reflectivity = 0.15;
    spheres[NUM_SPHERES-1].position = v(0,-201,0);
    spheres[NUM_SPHERES-1].radius = 200.5;
    spheres[NUM_SPHERES-1].rayRadius = 200.505;
    spheres[NUM_SPHERES-1].mat.color = v(.2,.1,0);
    spheres[NUM_SPHERES-1].mat.reflectivity = 0.1;
  }
  v boundryColour(v position, v direction)
  {
    if (position%position < 64)
      return v(0,0,0);
    if (!direction % !sundir > 0.98)
      return v(9,9,9);
    else
      return v(0,0,0);
  };
};

#endif
