#pragma once

#include "glm/glm.hpp"

class Camera
{
public:
  Camera();
  Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up);
  ~Camera() {};

  glm::vec3 up, direction, position;

};