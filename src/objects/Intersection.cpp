#include "Intersection.h"



Intersection::Intersection()
  : tValue(FLT_MAX)
  , point(glm::vec3(0))
  , normal(glm::vec3(1))
{
}


Intersection::~Intersection()
{
}

void Intersection::copyFrom(Intersection & i)
{
  tValue = i.tValue;
  normal = i.normal;
  point = i.point;
}
