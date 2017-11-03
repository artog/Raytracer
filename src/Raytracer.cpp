#include "Raytracer.h"
#include "Graphics.h"
#include "glm/glm.hpp"

#include <thread>
#include <iostream>
#include <chrono>

using namespace glm;

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

    graphics->backBuffer.clear();
    graphics->backBuffer.resize(width*height);

    for (size_t i = 0; i < width*height; i++)
    {
        graphics->backBuffer[i].r = (i % width) / (float)width;
        if (mode % 2 == 0) {
          graphics->backBuffer[i].g = (i / width) / (float)height;
          graphics->backBuffer[i].b = 0.f;
        }
        else {
          graphics->backBuffer[i].g = 0.f;
          graphics->backBuffer[i].b = (i / width) / (float)height;
        }
    }
    graphics->pixelDataSize = glm::ivec2(width,height);
    graphics->swapBuffers();
}

void Raytracer::trace() {

  std::cout << "Starting trace." << std::endl;
  if (graphics == nullptr) {
    return;
  }

  reset(0);

  vec3 dx = vec3(2.f/graphics->width, 0, 0);
  vec3 dy = vec3(0, 2.f/graphics->width, 0);

  vec3 lowerLeft = scene.camera.direction + vec3(-dx.x*graphics->width/2, -dy.y*graphics->height/2, 1.f);

  for (GLuint x = 0; x < graphics->width;x++) {
    for (GLuint y = 0; y < graphics->height;y++) {

      Ray ray = Ray(scene.camera.position, normalize((lowerLeft + (float)x*dx + (float)y*dy)));
      Intersection intersection = Intersection();
      if (scene.intersect(ray,intersection)) {
        graphics->backBuffer[y*graphics->width + x] = vec3(1, (ray.d.y >= 0) ? 1 : 0, -intersection.point.z);
      } else {
        graphics->backBuffer[y*graphics->width + x] = vec3(0, (ray.d.y >= 0) ? 1 : 0, 0);
      }
      /*
      float scale = dot(ray.d, scene.camera.direction) / dot(ray.d, ray.d);
      */
    }
  }

  graphics->swapBuffers();
  std::cout << "Trace complete." << std::endl;
  /*
  for (int i = 0; i < 1000;i++) {
    std::cout << "Loop " << i << std::endl;
    reset(i);
    if (!graphics->isActive()) break;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  */
}



