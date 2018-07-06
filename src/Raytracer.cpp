#include "Raytracer.h"
#include "Graphics.h"
#include "glm/glm.hpp"
#include <iostream>

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

void Raytracer::reset()
{
    int &width = graphics->width;
    int &height = graphics->height;

    graphics->pixelData.clear();
    graphics->pixelData.resize(width*height);

    for (size_t i = 0; i < width*height; i++)
    {
        graphics->pixelData[i].r = (i % width) / (float)width;
        graphics->pixelData[i].g = (i / width) / (float)height;
        graphics->pixelData[i].b = 0.f;
    }
    graphics->pixelDataSize = glm::ivec2(width,height);
}

void Raytracer::trace() 
{
	std::cout << "Starting trace..." << std::endl;
	int &width = graphics->width;
	int &height = graphics->height;

	int sampleCount = 0, sampleLimit = 10000;

	while (sampleCount < sampleLimit) {

		for (size_t i = 0; i < width*height; i++)
		{
			graphics->pixelData[i].r *= 1.1f;
			graphics->pixelData[i].g *= 1.1f;
			graphics->pixelData[i].b *= 1.1f;
		}
		sampleCount++;
	}
	std::cout << "Trace complete!" << std::endl;
}

glm::vec3 Raytracer::sample(Geometry::Ray & r)
{
	return glm::vec3();
}
