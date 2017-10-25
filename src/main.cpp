#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Raytracer.h"
#include "Graphics.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "main.h"

void main(int* argc, char* argv[]) {
    
    
    Graphics graphics = Graphics();

    Raytracer raytracer = Raytracer(&graphics);
    
    graphics.init(640, 480);

    raytracer.init();
    std::thread raytracerThread = std::thread(&Raytracer::trace, raytracer);

    graphics.mainLoop();

    raytracerThread.join();
    graphics.finish();

}