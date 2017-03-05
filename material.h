#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "utils.h"
#include "ray.h"

struct scene;

struct material
{
  v color;
  float reflectivity;
  material();
  voxel getInteraction(v position, v normal, v direction, ray& callingRay, scene* parentScene);
};

#endif
