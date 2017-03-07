#include "raylog.h"
#include <vector>
#include <stdio.h>
#include <sys/time.h>
using namespace std;

map<long, long long> times;
long long start;

long long get_time()
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return tp.tv_usec;
}

void init_raylog()
{
}

void log_ray_start(ray& ry)
{
  times[ry.hash] = get_time();
}

void log_ray_end(ray& ry)
{
  times[ry.hash] = get_time() - times[ry.hash];
}

void print_raylog()
{
  long average = 0;
  for (pair<long,long> t : times)
    average += t.second;
  average /= times.size();
  fprintf(stderr,"Total rays: %d\n",times.size());
  fprintf(stderr,"Average time per ray: %.3fms\n",average/1000000.);
}
