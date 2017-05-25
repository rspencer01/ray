#include "scene.h"
#include "sphere.h"

scene::scene()
{
  width = height = 100;
  ambient = 0.1;
  sundir = !v(1.3,1,-0.4);
  for (int i = 0; i < 80; ++i)
  {
    objects.push_back(new sphere(this));
    ((sphere*)(objects.back()))->radius = 0.1;
    objects.back()->rayRadius = 0.11;
    objects.back()->mat.transmittance = 0.8;
    objects.back()->mat.reflectivity = 0.9;
    objects.back()->mat.color = v(0.7,0.8,1.0);
  }

  objects.push_back(new sphere(this));
  objects.back()->position =  v(0,-10,1.0);
  ((sphere*)(objects.back()))->radius = 9.2;
  objects.back()->rayRadius = 9.3;
  objects.back()->mat.transmittance = 0;
  objects.back()->mat.color = v(0.1,0.2,0.1);
}


v scene::boundryColour(v position, v direction)
{
  if (norm(position) < 8)
    return v(0,0,0);
  if (!direction % !sundir > 0.98)
    return v(9,9,9);
  else
    return v(0,0,0);
}
