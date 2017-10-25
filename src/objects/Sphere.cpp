#include "Sphere.h"



Sphere::Sphere(glm::vec3 position, float radius, glm::vec3 color)
  : position(position)
  , color(color)
  , radius(radius)
{
}

bool Sphere::intersectsWith(Ray & r, Intersection & intersection)
{
  return false;
}

