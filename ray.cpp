#include <stdio.h>
#include <math.h>
#include "vector3.h"
#include "utils.h"
#include "ray.h"
#include "raylog.h"
#include "sphere.h"
#include "scene.h"

scene current_scene;

double d = 1e-2;
#define RAY_LENGTH 10
void trace(ray&);
const char* _help =
"Usage: ray <scenefile>";

voxel integrand(v pos, v dir, int level,ray calling)
{
  voxel ans;
  for (object* o : current_scene.objects)
  {
    voxel p = o->intersects(pos, pos+dir*d,dir,calling);
    if (p.perm>-0)
    {
      return p;
    }
  }
  return ans;
}

v nextPosition(v position, v direction, double maxD)
{
  double minLambda = maxD;
  for (object* o : current_scene.objects)
  {
    if (norm(position - o->position) < o->rayRadius)
    {
      minLambda = d;
      break;
    }
    if (intersectSphere(o->position,
                        o->rayRadius,
                        position,
                        direction))
    {
      minLambda = std::min(
                           minLambda,
                           intersectSphereDist(
                                               o->position,
                                               o->rayRadius,
                                               position,
                                               direction));
    }
  }
  minLambda = std::max(d, minLambda);
  return position + !direction * minLambda;
}

void trace(ray &ry)
{
  // Cutoff integration after two bounces
  if (ry.level > 2)
    return;
  // Log that we executed this ray
  log_ray_start(ry);

  double p = 1;
  // Begin with black
  // TODO can we change this up?
  v color = v(0,0,0);
  // The position used during integration
  v position = ry.position;
  while ((position-ry.position)%(position-ry.position) < RAY_LENGTH*RAY_LENGTH)
  {
    log_ray_integrate(ry);
    voxel immediate;
    // Calculate the color at this point in space (`immediate`) along
    // with its alpha (`trans`)
    immediate = integrand(position, ry.direction, ry.level+1, ry);
    // Update the color
    color = color + immediate.local_color * p * immediate.perm;
    for (int j = 0; j<immediate.ray_contributions.size();++j)
    {
      trace(immediate.ray_contributions[j].first);
      color = color +immediate.ray_contributions[j].first.color*immediate.ray_contributions[j].second * immediate.perm * p;
    }

    // Update the transmission coefficient
    p *= clamp(1-immediate.perm,0,1);
    // If any of the objects just hit killed the ray, break out of this
    // loop
    if (not ry.alive or p < 0.001) break;
    // Update the inegration position
    position = nextPosition(position, ry.direction, RAY_LENGTH);
  }
  // We may have some transmission "left over".  Colour
  // the point at infinity the default color of the scene
  color = color + current_scene.boundryColour(position,ry.direction)* p;

  // Update the returned ray struct with the calculated
  // color and notify the calling code that the trace
  // executed sucessfully
  ry.color = color;
  ry.completed = true;

  // Finally, log that this ray is complete
  log_ray_end(ry);
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, _help);
    return 1;
  }
  current_scene.loadFromFile(argv[1]);

  init_raylog();

  FILE* outputFile = fopen("out.ppm","wb");
  // Output preamble
  fprintf(outputFile,"P6 %d %d 255 ",current_scene.width ,current_scene.height);
  // Camera viewpoint
  v viewpoint = v(0,0,-1);
  // Iterate through all pixels in screen
  for(int y=current_scene.height; y--;)
  {
    // Pretty progress bar
    for (int i = 80 - 80*y/current_scene.height; i--;)
      printf("o");
    for (int i = 80*y/current_scene.height; i--;)
      printf(".");
    printf("\r"); fflush(stdout);
    for(int x=current_scene.width; x--;)
    {
      // Calculate the direction for this pixel
      v direction = calculateDirection(x/(double)current_scene.width, y/(double)current_scene.height);
      // Construct the ray
      ray primary = ray(viewpoint, direction, v(0,0,0), 0);
      // Trace the ray
      trace(primary);
      // Pos processing
      v pixel = primary.color*255;
      // Atan to prevent overbrightness
      pixel.x = atan(pixel.x/100)/(3.1415/2)*255;
      pixel.y = atan(pixel.y/100)/(3.1415/2)*255;
      pixel.z = atan(pixel.z/100)/(3.1415/2)*255;
      // Output to image
      fprintf(outputFile,"%c%c%c",(unsigned int)pixel.x,(unsigned int)pixel.y,(unsigned int)pixel.z);
    }
  }
  fclose(outputFile);
  print_raylog();
}
