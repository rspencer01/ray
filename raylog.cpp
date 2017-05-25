#include "raylog.h"
#include <vector>
#include <stdio.h>
#include <sys/time.h>
using namespace std;

map<long, long long> times;
map<long, long long> integrands;
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
  integrands[ry.hash] = 0;
}

void log_ray_integrate(ray& ry)
{
  integrands[ry.hash]++;
}

void log_ray_end(ray& ry)
{
  times[ry.hash] = get_time() - times[ry.hash];
}

void print_raylog()
{
  fprintf(stderr,"Total rays: %d\n",times.size());
  long average = 0;
  for (pair<long,long> t : times)
    average += t.second;
  average /= times.size();
  fprintf(stderr,"Average time per ray: %.3fms\n",average/1000000.);

  average = 0;
  for (pair<long,long> t : integrands)
    average += t.second;
  average /= integrands.size();
  fprintf(stderr,"Average integrands per ray: %ld\n",average);
}
