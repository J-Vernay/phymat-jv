#pragma once

#include <utility>

#include "GLFW/glfw3.h"
#include "imgui.h"

#include "Particle.hpp"

/// Represents keyboard game control.
struct Controls {
    bool left = false, up = false, right = false, down = false;
};

/// Class responsible for GLFW, OpenGL and ImGui management.
class Window {
public:
    // The constructor will initialize GLFW, OpenGL and ImGui.
    Window();
    Window(Window const&) = delete; // No copy allowed.
    ~Window() noexcept;

    /// Setup OpenGL and ImGui for a new frame.
    void begin_frame();
    /// Setup ImGui for a new frame.
    void begin_ui();
    /// Finish ImGui.
    void end_ui();
    /// Finish frame and swap to screen. 
    void end_frame();

    /// Return dimensions of window.
    std::pair<int, int> size() const { return { _width, _height }; }

    bool should_close() const noexcept { return glfwWindowShouldClose(_window); }

    Controls getControls() const { return _controls; }
    
private:
    GLFWwindow* _window;
    Controls _controls;
    int _width, _height;
};

/// Structure holding all informations needed for camera.
struct Camera {
    float target[3] = {0,0,0}; ///< Where the camera is looking at.
    float distance = 10;       ///< How far is the camera from the target.
    float fieldOfView = 70;    ///< Field of view in degrees.
    float angle[2] = {0,30};   ///< Horizontal and vertical angles in degrees.
};

/// Shows the ImGui UI for controlling camera.
void ask_camera_ui(Camera& camera);

/// Setup matrixes for GL_PROJECTION and GL_MODELVIEW appropriate for the given camera.
void use_camera_gl(Window const& window, Camera const& camera);

/// Class responsible to render a particle into OpenGL.
class ParticleRenderer {
public:
    ParticleRenderer();
    ~ParticleRenderer();

    void draw(Particle const& p);

    void draw(Vector3 pos, Vector3 color, float radius);

private:
    GLUquadric* _quadric;
};
