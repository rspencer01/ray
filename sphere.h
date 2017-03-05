#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "vector3.h"
#include "utils.h"
#include "ray.h"
#include "material.h"
#include "object.h"

struct scene;

struct sphere : public object
{
  float radius;
  material mat;
  sphere(scene* _parentScene) : object(_parentScene)
  {
    parentScene = _parentScene;
    position = v(2*R()-1,2*R()-1,R()+1);
    radius = R()/6;
    rayRadius = radius*1.01;
  };
  voxel intersects(v position, v nextPosition, v direction, ray& callingRay);
};

#include "scene.h"

voxel sphere::intersects(v position, v nextPosition, v direction, ray& callingRay)
{
  voxel ans;
  float currentRadius2 = (position - this->position)%(position - this->position);
  float nextRadius2 = (nextPosition - this->position)%(nextPosition - this->position);
  v norm = !(position - this->position);
  if ((currentRadius2 > this->radius * this->radius)
    and (nextRadius2 < this->radius * this->radius))
  {
    callingRay.alive = false;
    ans.perm = 1;
    ans.local_color = this->mat.color * parentScene->ambient * (1-mat.reflectivity);

    ray rf = ray(position,!mirror(direction*-1,norm),v(0,0,0),callingRay.level+1);
    ans.ray_contributions.push_back(std::make_pair(rf,v(1,1,1)*mat.reflectivity));

    float f = (!parentScene->sundir)%(!(position-this->position));
    if (f<=0)
      return ans;
    ray sd = ray(position,parentScene->sundir,v(0,0,0),callingRay.level+1);
    ans.ray_contributions.push_back(std::make_pair(sd,this->mat.color*f*(1-mat.reflectivity)));
    return ans;
  }
};
#endif
