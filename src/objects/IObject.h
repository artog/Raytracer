#pragma once
#include "Ray.h"
#include "Intersection.h"

class IObject
{
public: 
  virtual ~IObject() {};
  virtual void render() = 0;
  virtual bool intersectsWith(Ray &r, Intersection &intersection) = 0;
};