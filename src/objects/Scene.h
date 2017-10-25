#pragma once

#include <vector>
#include <memory>

#include "Ray.h"
#include "Intersection.h"
#include "IObject.h"

class Scene
{
public:
  Scene();
  ~Scene();

private:
  std::vector<std::unique_ptr<IObject>> objects;
};

