#pragma once

#include <vector>
#include <memory>

#include "Ray.h"
#include "Intersection.h"
#include "Camera.h"
#include "IObject.h"
#include "Sphere.h"

class Scene
{
public:
  Scene();
  ~Scene();

  bool intersect(Ray &ray, Intersection &intersection);
  bool anyIntersect(Ray &ray, Intersection &intersection);

  Camera camera;

private:
  std::vector<std::unique_ptr<IObject>> objects;
};

