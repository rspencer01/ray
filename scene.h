#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "vector3.h"
#include "sphere.h"
#include "object.h"

#define NUM_SPHERES 10

struct scene
{
  v sundir;
  std::vector<object*> spheres;
  float ambient;
  scene()
  {
    ambient = 0.1;
    sundir = !v(1.3,1,-0.4);
    for (int i = 0; i< NUM_SPHERES;++i)
      spheres.push_back(new sphere(this));
    ((sphere*)spheres[0])->position = v(.8,0,2);
    ((sphere*)spheres[0])->radius = 0.5;
    ((sphere*)spheres[0])->rayRadius = 0.505;
    ((sphere*)spheres[0])->mat.color = v(0,0.1,0);
    ((sphere*)spheres[0])->mat.reflectivity = 0.13;
    ((sphere*)spheres[1])->position = v(-.8,-.1,2.05);
    ((sphere*)spheres[1])->radius = 0.5;
    ((sphere*)spheres[1])->rayRadius = 0.505;
    ((sphere*)spheres[1])->mat.color = v(0,0,0.1);
    ((sphere*)spheres[1])->mat.reflectivity = 0.15;
    ((sphere*)spheres[NUM_SPHERES-1])->position = v(0,-201,0);
    ((sphere*)spheres[NUM_SPHERES-1])->radius = 200.5;
    ((sphere*)spheres[NUM_SPHERES-1])->rayRadius = 200.505;
    ((sphere*)spheres[NUM_SPHERES-1])->mat.color = v(.2,.1,0);
    ((sphere*)spheres[NUM_SPHERES-1])->mat.reflectivity = 0.1;
  }

  v boundryColour(v position, v direction)
  {
    if (norm(position) < 8)
      return v(0,0,0);
    if (!direction % !sundir > 0.98)
      return v(9,9,9);
    else
      return v(0,0,0);
  };
};

#endif
