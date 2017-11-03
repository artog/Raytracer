#include "Sphere.h"
#include "glm/glm.hpp"

using namespace glm;

Sphere::Sphere(glm::vec3 position, float radius, glm::vec3 color)
  : position(position)
  , color(color)
  , radius(radius)
  , radius2(radius*radius)
{
}

bool Sphere::intersectsWith(Ray &r, Intersection &intersection)
{
  vec3 a = position - r.o;
  vec3 &b = r.d;

  float t = dot(a, b) / dot(b, b);
  vec3 ref = r.o + t*r.d;
  vec3 d = position - ref;
  float d2 = dot(d, d);
  float offset = sqrt(radius2 - d2);

  if (d2 <= radius2) {
    intersection.tValue = t;
    intersection.point  = r.o + (t-offset)*r.d;
    intersection.normal = normalize(intersection.point - position);
    return true;
  }

  return false;
}

