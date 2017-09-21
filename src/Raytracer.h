#pragma once
#include "glm/glm.hpp"

class Graphics;

class Raytracer
{
public:
    Raytracer(Graphics* const graphics);
    ~Raytracer();

    void init();
    void reset();

    Graphics* const graphics;
    glm::vec3 *frameBuffer;
    glm::ivec2 frameBufferSize;

};

