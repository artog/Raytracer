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

    //std::thread raytracerThread([graphics]() {
        Raytracer raytracer = Raytracer(&graphics);
    //});
    graphics.init(640, 480);

    //graphics.start();
    raytracer.init();

    graphics.mainLoop();

    graphics.finish();

}