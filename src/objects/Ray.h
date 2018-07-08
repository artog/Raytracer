#pragma once

#include "glm/glm.hpp"

class Ray
{
public:
  Ray(glm::vec3 origin, glm::vec3 direction);
  ~Ray();

  glm::vec3 o, d;

};

