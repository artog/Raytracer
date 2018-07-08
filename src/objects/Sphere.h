#pragma once
#include "IObject.h"
#include "glm/glm.hpp"


class Sphere :
  public IObject
{
public:
  Sphere(glm::vec3 position, float radius, glm::vec3 color);

  bool intersectsWith(Ray &r, Intersection &intersection) override;
  void render() override {};

private:
  glm::vec3 position;
  glm::vec3 color;
  float radius, radius2;
};

