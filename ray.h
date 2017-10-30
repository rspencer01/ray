#ifndef __RAY_H__
#define __RAY_H__

#include "vector3.h"
#include <bits/stdc++.h>

struct ray
{
  v position;
  v direction;
  v color;
  bool completed;
  int level;
  bool alive;
  long hash;
  int pixelx, pixely;

  ray()
  {
    completed = false;
    alive = true;
    hash = rand();
    pixelx = pixely = -1;
  };

  ray(v _position, v _direction, v _color=v(0,0,0), int _level=0)
  {
    position = _position;
    direction = _direction;
    color = _color;
    level = _level;
    completed = false;
    alive = true;
    hash = rand();
    pixelx = pixely = -1;
  };
};

struct voxel
{
  double perm;
  v local_color;
  std::vector<std::pair<ray,v> > ray_contributions;
  voxel()
  {
    perm = 0.;
    ray_contributions.clear();
  };
  voxel(double _perm, v _local_color=v(0,0,0))
  {
    perm = _perm;
    local_color = _local_color;
    ray_contributions.clear();
  };
};
#endif
