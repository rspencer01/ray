#include <stdio.h>
#include <math.h>
#include "vector3.h"
#include "utils.h"
#include "gui.h"
#include "ray.h"
#include "raylog.h"
#include "sphere.h"
#include "scene.h"

scene current_scene;

double d = 1e-2;
#define RAY_LENGTH 10
void trace(ray&);
unsigned char* buffer;
FILE* outputFile;
const char* _help =
"Usage: ray <scenefile>";

voxel integrand(v pos, v dir, int level,ray& calling)
{
  voxel ans;
  ans.perm = 0;
  ans.local_color = v(0,0,0);
  for (object* o : current_scene.objects)
  {
    voxel p = o->intersects(pos, pos+dir*d, dir, calling);
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
                                               direction)*0.9);
    }
  }
  minLambda = std::max(d, minLambda);
  return position + !direction * minLambda;
}

void update_pixels_from_primary_ray(ray& ry)
{
  // Post processing
  v pixel = ry.color*255;
  // Atan to prevent overbrightness
  pixel.x = atan(pixel.x/100)/(3.1415/2)*255;
  pixel.y = atan(pixel.y/100)/(3.1415/2)*255;
  pixel.z = atan(pixel.z/100)/(3.1415/2)*255;
  // Output to image
  buffer[(current_scene.height-1-ry.pixely)*current_scene.width*3 + ry.pixelx*3  ] = (unsigned char)pixel.x;
  buffer[(current_scene.height-1-ry.pixely)*current_scene.width*3 + ry.pixelx*3+1] = (unsigned char)pixel.y;
  buffer[(current_scene.height-1-ry.pixely)*current_scene.width*3 + ry.pixelx*3+2] = (unsigned char)pixel.z;
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
    color = color + immediate.local_color * p;
    for (int j = 0; j<immediate.ray_contributions.size();++j)
    {
      trace(immediate.ray_contributions[j].first);
      color = color + immediate.ray_contributions[j].first.color*immediate.ray_contributions[j].second * p;
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

  // Update the image if needbe
  if (ry.pixelx != -1)
    update_pixels_from_primary_ray(ry);

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
  init_window();

  init_raylog();

  // Camera viewpoint
  v viewpoint = v(0,0,-1);
  // The buffer
  buffer = new unsigned char[current_scene.height*current_scene.width*3];
  // Iterate through all pixels in screen
  int count = 0;
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
      primary.pixelx = x;
      primary.pixely = y;
      // Trace the ray
      trace(primary);
      // Display
      if (count%(current_scene.height/3) == 0)
        update_image(buffer, current_scene.height, current_scene.width);
      count++;
    }
  }
  // Write to output
  outputFile = fopen("out.ppm","wb");
  // Output preamble
  fprintf(outputFile,"P6 %d %d 255 ",current_scene.width ,current_scene.height);
  for(int y=current_scene.height; y--;)
    for(int x=current_scene.width; x--;)
      for(int k=0;k<3;++k)
      fprintf(outputFile,"%c",buffer[y*current_scene.width*3 + x*3 + k]);
  fclose(outputFile);
  print_raylog();
  gui_pause();
  destroy_window();
}
