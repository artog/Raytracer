#pragma once
#include "glm/glm.hpp"
#include <thread>

#include "objects/Scene.h"

class Graphics;

class Raytracer
{
public:

    Raytracer(Graphics* const graphics);
    ~Raytracer();

    /** Copy constructor */
    Raytracer(const Raytracer& other) :
      graphics(other.graphics)
    {

    }

    /** Copy assignment operator */
    Raytracer& operator= (const Raytracer& other)
    {
      Raytracer tmp(other);   // re-use copy-constructor
      *this = std::move(tmp); // re-use move-assignment
      return *this;
    }

    /** Move assignment operator */
    Raytracer& operator= (Raytracer&& other) noexcept
    {
      delete[] graphics;
      graphics = other.graphics;
      other.graphics = nullptr;
      return *this;
    }

    /** Move constructor */
    Raytracer(Raytracer&& other) noexcept : /* noexcept needed to enable optimizations in containers */
        graphics(other.graphics)
    {
      other.graphics = nullptr;
    }

    void init();
    void reset(int mode = 0);
    void trace();

    Graphics* graphics;
    Scene scene;

    bool isActive = true;

    std::thread traceThread;


};

