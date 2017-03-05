#include "material.h"
#include "scene.h"

material::material()
{
  color = v(R(),R()/3,R()/2);
  reflectivity = R()*0.8;
}

voxel material::getInteraction(v position, v normal, v direction, ray& callingRay, scene* parentScene)
{
  voxel ans;
  callingRay.alive = false;
  ans.perm = 1;
  ans.local_color = color * parentScene->ambient * (1-reflectivity);

  ray rf = ray(position,!mirror(direction*-1,normal),v(0,0,0),callingRay.level+1);
  ans.ray_contributions.push_back(std::make_pair(rf,v(1,1,1)*reflectivity));

  float f = (!parentScene->sundir)%normal;
  if (f<=0)
    return ans;
  ray sd = ray(position,parentScene->sundir,v(0,0,0),callingRay.level+1);
  ans.ray_contributions.push_back(std::make_pair(sd,color*f*(1-reflectivity)));
  return ans;
}
