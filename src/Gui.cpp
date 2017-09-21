#include "Gui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

Gui::Gui() {

}

Gui::~Gui() {
}


void Gui::init(GLFWwindow *window) {
    ImGui_ImplGlfwGL3_Init(window, true);
}

void Gui::render() {

    ImGui_ImplGlfwGL3_NewFrame();

    bool isOpen = true;
    ImGui::Begin("Info", &isOpen, 0);

    ImGui::Text("Window.");

    ImGui::End();

    ImGui::Render();
}

void Gui::finish()
{
    ImGui_ImplGlfwGL3_Shutdown();
}
