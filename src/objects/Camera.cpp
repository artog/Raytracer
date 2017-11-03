#include "Camera.h"


Camera::Camera()
  : up(glm::vec3(0.f,1.f,0.f))
  , direction(glm::vec3(0,0,1))
  , position(glm::vec3(0,0,-5))
{

};

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
  : position(position)
  , direction(direction)
  , up(up)
{

};
