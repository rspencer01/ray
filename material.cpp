#include "material.h"
#include "scene.h"

material::material()
{
  color = v(R(),R()/3,R()/2);
  reflectivity = R()*0.8;
  transmittance = R()*0.8;
  ior = 1.3;
}

voxel material::getInteraction(
    v position,
    v normal,
    v direction,
    ray& callingRay,
    scene* parentScene)
{
  voxel ans;
  ans.perm = 1-transmittance;
  ans.local_color = color * parentScene->ambient;

  // Reflective ray
  ray rf = ray(position,!mirror(direction*-1,normal),v(0,0,0),callingRay.level+1);
  ans.ray_contributions.push_back(std::make_pair(rf,v(1,1,1)*reflectivity));

  // Sun facing light ray
  float f = (!parentScene->sundir)%normal;
  ray sd = ray(position,parentScene->sundir,v(0,0,0),callingRay.level+1);
  if (f>0)
    ans.ray_contributions.push_back(std::make_pair(sd,color*f));

  callingRay.direction = refract(direction, normal, ior);
  return ans;
}
