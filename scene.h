#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "vector3.h"
#include "sphere.h"
#include "object.h"
#include "cube.h"

struct scene
{
  v sundir;
  std::vector<object*> spheres;
  float ambient;
  scene()
  {
    ambient = 0.1;
    sundir = !v(1.3,1,-0.4);
    for (int i = 0; i< 10; ++i)
      objects.push_back(new cube(this));

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
