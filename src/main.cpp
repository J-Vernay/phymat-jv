#if 0
#include "Graphics.hpp"

int main() {
    glfwInit();
    // Create window.
    int size[2] = {800,600};
    GLFWwindow* window = glfwCreateWindow(size[0], size[1], "Projet Sephiroth", NULL, NULL);
    glfwSetWindowUserPointer(window, size);
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int x, int y) {
        int* size = (int*)glfwGetWindowUserPointer(window);
        size[0] = x; size[1] = y;
    });


    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Setup OpenGL for new frame.
        glViewport(0, 0, size[0], size[1]);
        glClearColor(0.3, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0);
        glVertex3f(0.5, 0.5, 0.2);
        glVertex3f(0.5, 0, 0.2);
        glVertex3f(0, 0, 0.2);
        glColor3f(1, 1, 0);
        glVertex3f(1, 1, 0.1);
        glVertex3f(1, 0, 0.1);
        glVertex3f(0, 0, 0.1);
        glEnd();
        glFlush();

        glfwSwapBuffers(window);
    }
}

#else
#include <iostream>

#include "Graphics.hpp"
#include "Spawner.hpp"
#include "Integrator.hpp"

void draw_floor() {
    const int FloorSize = 20;
    // Draw actual floor.
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
}

int main() {

    Window window;
    Camera camera;
    Integrator integrator;
    Spawner spawner(integrator);

    Projectile projectile;

    // Disable use of configuration file.
    ImGui::GetIO().IniFilename = nullptr;

    // Main loop.
    while (!window.should_close()) {
        spawner.update(glfwGetTime()); 
        integrator.updateAll();


        // Start drawing for this frame.
        glClearColor(0.3, 0.7, 0.9, 1);
        glEnable(GL_DEPTH_TEST);
        window.begin_frame();

        // World drawings.
        use_camera_gl(window,camera);
        draw_floor();
        for(auto &p : integrator.getParticleList()) {
            // Draw each particle according to its type.
            glPushMatrix();
            glTranslatef(p.getPosition().getx(),p.getPosition().gety(),p.getPosition().getz());
            projectile.draw(p.getType());
            glPopMatrix();
        }


        // GUI drawings.
        window.begin_ui();
        ask_camera_ui(camera);
        spawner.ask_ui();
        window.end_ui();

        // Finalizes GUI and show drawings to screen.
        window.end_frame();
    }


    return 0;
}

#endif