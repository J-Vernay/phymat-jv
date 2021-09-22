#include <iostream>

#include "Matrix.hpp"
#include "Graphics.hpp"
#include "Spawner.hpp"
#include "Integrator.hpp"

int main() {

    Window window;
    Camera camera;
    Integrator integrator;
    Spawner spawner(integrator);

    ImGui::GetIO().IniFilename = nullptr;
    
    // Main loop.
    while (!window.should_close()) {
        spawner.update(glfwGetTime());

        glClearColor(0.3, 0.7, 0.9, 1);

        window.begin_frame();
        use_camera_gl(window, camera);


        const int FloorSize = 20;

        // Draw floor.
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.5, 0.8, 0.5);
        glVertex3f(-FloorSize, -FloorSize, 0);
        glVertex3f(-FloorSize, +FloorSize, 0);
        glVertex3f(+FloorSize, +FloorSize, 0);
        glVertex3f(+FloorSize, -FloorSize, 0);
        glEnd();


        // Draw grid.
        glBegin(GL_LINES);
        glColor3f(0.2, 0.6, 0.2);
        for (int i = -FloorSize; i <= FloorSize; ++i) {
            glVertex3f(-FloorSize, i, 0.01);
            glVertex3f(+FloorSize, i, 0.01);
            glVertex3f(i, -FloorSize, 0.01);
            glVertex3f(i, +FloorSize, 0.01);
        }
        glEnd();

        // Making an animated rotation.
        glRotatef((float)glfwGetTime() * 50, 0, 0, 1);

        // Draw a triangle.
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0.1);
        glVertex3f(-0.6, -0.4, 0.02);
        glColor3f(0, 0, 1);
        glVertex3f(0, 0.6, 0.02);
        glColor3f(0, 1, 0);
        glVertex3f(0.6, -0.4, 0.02);
        glEnd();
        
        ask_camera_ui(camera);
        spawner.ask_ui();


        window.end_frame();
    }


    return 0;
}

