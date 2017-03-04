#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "utils.h"

struct material
{
  v color;
  float reflectivity;
  material()
  {
    color = v(R(),R()/3,R()/2);
    reflectivity = R()*0.8;
  };
};

#endif
