#include "scene.h"
#include "sphere.h"
#include "glob.h"

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

void scene::loadFromFile(const char* filename)
{
  FILE* fp = fopen(filename, "r");
  objects.clear();
  char inst;
  material mat;
  while (not feof(fp))
  {
    fscanf(fp, " %c", &inst);
    if (feof(fp)) break;
    switch (inst)
    {
      case 'w':
        fscanf(fp, "%d", &width);
        break;
      case 'h':
        fscanf(fp, "%d", &height);
        break;
      case 's':
        double x,y,z,r;
        fscanf(fp, "%lf %lf %lf %lf", &x, &y, &z, &r);
        fprintf(stderr, "%lf %lf %lf %lf\n",x,y,z,r);
        objects.push_back(new sphere(this));
        ((sphere*) objects.back())->position = v(x,y,z);
        ((sphere*)(objects.back()))->radius = r;
        objects.back()->rayRadius = r*1.01;
        objects.back()->mat = mat;
        break;

      case 'm':
        double g,b, ref, trans;
        fscanf(fp, "%lf %lf %lf %lf %lf", &r, &g, &b, &ref, &trans);
        mat.color.x = r;
        mat.color.y = g;
        mat.color.z = b;
        mat.reflectivity = ref;
        mat.transmittance = trans;
        break;

      case 'g':
        int c;
        fscanf(fp, "%d %lf %lf", &c, &x, &y);
        objects.push_back(new glob(this));
        objects.back()->mat = mat;
        ((glob*)objects.back())->sigma = y;
        ((glob*)objects.back())->setRadius(x);
        for (int i = 0; i < c; ++i)
        {
          fscanf(fp, "%lf %lf %lf", &x, &y, &z);
          ((glob*)objects.back())->addControl(v(x,y,z));
        }
        break;
      default:
        break;
    }
  }
}
