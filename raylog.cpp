#include "raylog.h"

int ray_count;

void init_raylog()
{
  ray_count = 0;
}

void log_ray_start(ray& ry)
{
  ray_count++;
}

void log_ray_end(ray& ry)
{
}

void print_raylog()
{
  fprintf(stderr,"Total rays: %d\n",ray_count);
}
