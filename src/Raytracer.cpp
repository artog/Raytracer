#include "Raytracer.h"
#include "Graphics.h"
#include "glm/glm.hpp"

#include <thread>
#include <iostream>
#include <chrono>

// using namespace glm;

Raytracer::Raytracer(Graphics * const g)
   : graphics(g)
{

}


Raytracer::~Raytracer()
{
}

void Raytracer::init()
{
    reset();
}

void Raytracer::reset(int mode)
{
    GLuint &width = graphics->width;
    GLuint &height = graphics->height;

    graphics->pixelData.clear();
    graphics->pixelData.resize(width*height);

    for (size_t i = 0; i < width*height; i++)
    {
        graphics->pixelData[i].r = (i % width) / (float)width;
        if (mode % 2 == 0) {
          graphics->pixelData[i].g = (i / width) / (float)height;
          graphics->pixelData[i].b = 0.f;
        }
        else {
          graphics->pixelData[i].g = 0.f;
          graphics->pixelData[i].b = (i / width) / (float)height;
        }
    }
    graphics->pixelDataSize = glm::ivec2(width,height);
}

void Raytracer::trace() {
  if (graphics != nullptr) {

  }
  for (int i = 0; i < 1000;i++) {
    std::cout << "Loop " << i << std::endl;
    reset(i);
    if (!graphics->isActive()) break;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}



