#pragma once
#include "glm/glm.hpp"
#include "Geometry/Ray.h"
class Graphics;

class Raytracer
{
public:
    Raytracer(Graphics* const graphics);
    ~Raytracer();

    void init();
    void reset();
	void trace();
	glm::vec3 sample(Geometry::Ray &r);

    Graphics* const graphics;
    glm::vec3 *frameBuffer;
    glm::ivec2 frameBufferSize;

};

