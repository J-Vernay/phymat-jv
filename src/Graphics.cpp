#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Graphics.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

#include <stdexcept>

Window::Window() {
    if (!glfwInit())
        throw std::runtime_error("Could not initialize GLFW");

    // Create window.
    _width = 800;
    _height = 800;
    _window = glfwCreateWindow(_width, _height, "Projet Sephiroth", NULL, NULL);
    if (!_window) {
        glfwTerminate();
        throw std::runtime_error("Could not open GLFW window");
    }

    // Initializes ImGui.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL2_Init();

    // OpenGL initial setup.
    glEnable(GL_DEPTH_TEST);

    // Event handling.
    glfwSetWindowUserPointer(_window, this);
    glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int x, int y) {
        Window* w = (Window*)glfwGetWindowUserPointer(window);
        w->_width = x;
        w->_height = y;
    });
}

void Window::begin_frame() {
    // Before starting a new frame, check events.
    glfwPollEvents();
    glfwMakeContextCurrent(_window);

    // Setup OpenGL for new frame.
    glViewport(0, 0, _width, _height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Window::begin_ui() {
    // Setup ImGui for new frame.
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::end_ui() {
    // Push ImGui state to OpenGL.
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void Window::end_frame() {
    // Show drawings to current window.
    glfwSwapBuffers(_window);

}

Window::~Window() noexcept {
    glfwDestroyWindow(_window);
    glfwTerminate();
}



#include <cmath>

// Trigonometric functions working in degrees.
float cosd(float deg) { return std::cos(deg * (M_PI / 180)); }
float sind(float deg) { return std::sin(deg * (M_PI / 180)); }

void ask_camera_ui(Camera& camera) {
    // Positionning window manually for the first frame.
    ImGui::SetNextWindowPos({ 50,50 }, ImGuiCond_Once);

    if (ImGui::Begin("Camera", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::SliderFloat3("Cible", camera.target, -20, 20);
        ImGui::SliderFloat("Distance", &camera.distance, 0, 10);
        ImGui::SliderFloat("Angle Horiz.", &camera.angle[0], -180, 180);
        ImGui::SliderFloat("Angle Vert.", &camera.angle[1], -90, 90);
        ImGui::SliderFloat("Champ de vue", &camera.fieldOfView, 30, 175);
    }
    ImGui::End();
}

void use_camera_gl(Window const& window, Camera const& camera) {
    // Apply perspective matrix.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    auto [w, h] = window.size();
    gluPerspective(camera.fieldOfView, (float)(w) / h, 1, 50);

    // Apply camera matrix.
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

// Constructor of the projectile object
Projectile::Projectile() {
    projectileQuadric_ = gluNewQuadric();
    gluQuadricDrawStyle(projectileQuadric_, GLU_FILL);
    gluQuadricNormals(projectileQuadric_, GLU_SMOOTH);
    gluQuadricTexture(projectileQuadric_, GL_FALSE);
}

// Destructor of the projectile object
Projectile::~Projectile() {
    gluDeleteQuadric(projectileQuadric_);
}

// Method to draw a specific kind of projectile
void Projectile::draw(int type) {
    switch (type) {
    // The projectile is a heavy ball
    case 0: {
        // Apply some material to add depth to the ball
        GLfloat ambient[] = { 0.05,0.05,0.05,1. };
        GLfloat diffuse[] = { 0.15,0.15,0.15 };
        GLfloat specular[] = { 0.4,0.4,0.4 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 50);
        // Apply some color to the ball
        glColor3f(.2f, .2f, .2f);
        // Draw the ball
        gluSphere(projectileQuadric_, 1, 20, 20);
        break;
    }
    // The projectile is a bullet
    case 1: {
        // Apply some material to add depth to the bullet
        GLfloat ambient[] = { 0.25,0.25,0.25,1. };
        GLfloat diffuse[] = { 0.65,0.65,0.65 };
        GLfloat specular[] = { 0.8,0.8,0.8 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 50);
        // Apply some color to the bullet
        glColor3f(.7f, .7f, .7f);
        // Draw the bullet
        gluSphere(projectileQuadric_, 0.2, 20, 20);
        break;
    }
    // The projectile is a fireball
    case 2:
    {
        /* TODO: texture should work

        // Apply a specific texture to the fireball        
        GLuint tex;
        GLUquadric* sphere;
        glEnable(GL_DEPTH_TEST);
        int x, y, n;
        unsigned char* data = stbi_load("fireball.jpg", &x, &y, &n, 4);
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, tex);
        gluQuadricTexture(projectileQuadric_, GL_TRUE);
        gluQuadricNormals(projectileQuadric_, GLU_SMOOTH);
        gluSphere(projectileQuadric_, 0.8, 20, 20);
        break;
        */
    }
    }
}