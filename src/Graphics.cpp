#include "Graphics.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <stdexcept>
#include <thread>
#include "glutil.h"

#define VERTEX_SHADER_PATH "shaders/simple.vert.glsl"
#define FRAGMENT_SHADER_PATH "shaders/simple.frag.glsl"


void Graphics::render()
{
    glfwMakeContextCurrent(window);

    GLfloat ratio;
    //mat4 viewMatrix, modelViewProjectionMatrix, modelViewMatrix, projectionMatrix;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    /*
    Render from pixelmap
    */
    static GLuint framebufferTexture = 0;
    if (framebufferTexture == 0) glGenTextures(1, &framebufferTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F,
        pixelDataSize.x,
        pixelDataSize.y,
        0, GL_RGB, GL_FLOAT, pixelData.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glUniform1i(glGetUniformLocation(shaderProgram, "framebuffer"), 0);
    GLint numSamples = 1;
    glUniform1i(glGetUniformLocation(shaderProgram, "framebufferSamples"), numSamples);

    // Bind the vertex array object that contains all the vertex data.
    glBindVertexArray(vao);
    // enable vertex attribute arrays 0 and 1 for the currently bound vertex array object.
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glUseProgram(0);

    gui.render();
}

void Graphics::mainLoop()
{
    if (!initialized) {
        throw std::runtime_error("Main loop called when uninitialied");
    }

    active = true;
    while (!glfwWindowShouldClose(window))
    {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    active = false;
}


void Graphics::init(GLint width, GLint height)
{
    glfwSetErrorCallback(glutil::consoleErrorCallback);

    if (!glfwInit()) {
        glutil::fatal_error("Error initializing glfw.");
    }

    this->width = width;
    this->height = height;

    window = glfwCreateWindow(width, height, "Raytracing using a Photon Map", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        if (!gladLoadGL()) {
            glutil::fatal_error("Failed to initialize OpenGL context");
        }
    }
    
    // Define the positions for each of the three vertices of the triangle
    const float positions[] = {
        1.0f,   -1.0f, 0.0f,
        1.0f,	  1.0f, 0.0f,
        -1.0f,	 -1.0f, 0.0f,
        -1.0f,	  1.0f, 0.0f
    };
    // Create a handle for the position vertex buffer object
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);
    // Set the newly created buffer as the current one
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    // Send the vertex position data to the current buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    //******* Connect triangle data with the vertex array object *******
    glGenVertexArrays(1, &vao);
    // Bind the vertex array object
    // The following calls will affect this vertex array object.
    glBindVertexArray(vao);
    // Makes positionBuffer the current array buffer for subsequent calls.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    // Attaches positionBuffer to vao, in the 0th attribute location
    glVertexAttribPointer(0, 3, GL_FLOAT, false/*normalized*/, 0/*stride*/, 0/*offset*/);
    glEnableVertexAttribArray(0); // Enable the vertex position attribute

    shaderProgram = glutil::loadShader(
        VERTEX_SHADER_PATH,
        FRAGMENT_SHADER_PATH
    );
    
    gui.init(window);

    initialized = true;
}

void Graphics::start() {
    if (!initialized) {
        throw std::runtime_error("Start run when graphics wasn't initialized");
    }

    
}

void Graphics::finish()
{
    glfwDestroyWindow(window);

    gui.finish();

    glfwTerminate();

}


bool Graphics::isActive()
{
    return active;
}

