#include "Scene.h"
#include <memory>

#include "glm/glm.hpp"

using namespace glm;

Scene::Scene()
  : camera(Camera())
{
  objects.emplace_back(
    std::make_unique<Sphere>(vec3(0), 1.0f, vec3(1))
  );
}


Scene::~Scene()
{
}

bool Scene::anyIntersect(Ray & ray, Intersection & intersection)
{
  for (auto &&obj : objects)
  {
    if (obj->intersectsWith(ray, intersection)) {
      return true;
    }
  }
  return false;
}


bool Scene::intersect(Ray & ray, Intersection & intersection)
{
  Intersection tempIntersection;
  bool didIntersect = false;
  for (auto &&obj : objects)
  {
    if (obj->intersectsWith(ray, tempIntersection)) {
      didIntersect = true;
      if (tempIntersection.tValue > 0 
          && tempIntersection.tValue < intersection.tValue) {
        intersection.copyFrom(tempIntersection);
      }
    }
  }
  return didIntersect;
}
