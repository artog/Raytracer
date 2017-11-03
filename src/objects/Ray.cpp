#include "Ray.h"


using namespace glm;


Ray::Ray(vec3 origin, vec3 direction)
  : o(origin)
  , d(direction)
{
}


Ray::~Ray()
{
}
