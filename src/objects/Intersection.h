#pragma once

#include "glm/glm.hpp"


class Intersection
{
public:
  Intersection();
  ~Intersection();

  float tValue;
  glm::vec3 point;
  glm::vec3 normal;

  void copyFrom(Intersection &i);

};

