#include "Graphics.hpp"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl2.h"

#include <stdexcept>

Window::Window() {
    if (!glfwInit())
        throw std::runtime_error("Could not initialize GLFW");

    _window = glfwCreateWindow(800, 600, "Projet Sephiroth", NULL, NULL);
    if (!_window) {
        glfwTerminate();
        throw std::runtime_error("Could not open GLFW window");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL2_Init();

    glEnable(GL_DEPTH_TEST);
}

void Window::begin_frame() {
    glfwPollEvents();
        
    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::end_frame() {
    ImGui::Render();

    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    glfwMakeContextCurrent(_window);
    glfwSwapBuffers(_window);

}

Window::~Window() noexcept {
    glfwDestroyWindow(_window);
    glfwTerminate();
}



#include <cmath>

float cosd(float deg) { return std::cos(deg * (M_PI / 180)); }
float sind(float deg) { return std::sin(deg * (M_PI / 180)); }


void ask_camera_ui(Camera& camera) {
    if (ImGui::Begin("Camera")) {
        ImGui::SliderFloat3("Cible", camera.target, -20, 20);
        ImGui::SliderFloat("Distance", &camera.distance, 0, 10);
        ImGui::SliderFloat("Angle Horiz.", &camera.angle[0], -180, 180);
        ImGui::SliderFloat("Angle Vert.", &camera.angle[1], -90, 90);
        ImGui::SliderFloat("Champ de vue", &camera.fieldOfView, 30, 175);
    }
    ImGui::End();
}

void use_camera_gl(Camera const& camera) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera.fieldOfView, 1, 0.1, 50);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float cospitch = cosd(camera.angle[1]);
    float eyeX = camera.target[0] + camera.distance * cospitch * cosd(camera.angle[0]);
    float eyeY = camera.target[1] + camera.distance * cospitch * sind(camera.angle[0]);
    float eyeZ = camera.target[2] + camera.distance * sind(camera.angle[1]);
    gluLookAt(eyeX, eyeY, eyeZ,
              camera.target[0], camera.target[1], camera.target[2],
              0, 0, 1);
}