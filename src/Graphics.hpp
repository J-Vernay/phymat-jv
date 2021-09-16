#pragma once

#include "GLFW/glfw3.h"
#include "imgui/imgui.h"


/// Class responsible for GLFW, OpenGL and ImGui management.
class Window {
public:
    Window();
    Window(Window const&) = delete; // No copy allowed.
    ~Window() noexcept;

    /// Setup OpenGL and ImGui for a new frame.
    void begin_frame();
    /// Finish frame and swap to screen. 
    void end_frame();

    bool should_close() const noexcept { return glfwWindowShouldClose(_window); }
private:
    GLFWwindow* _window;
};

/// Structure holding all informations needed for camera.
struct Camera {
    float target[3] = {0,0,0};
    float distance = 5;
    float fieldOfView = 70; // degrees
    float angle[2] = {0,30}; // degrees
};

/// Shows the ImGui UI for controlling camera.
void ask_camera_ui(Camera& camera);

/// Setup matrixes for GL_PROJECTION and GL_MODELVIEW appropriate for the given camera.
void use_camera_gl(Camera const& infos);