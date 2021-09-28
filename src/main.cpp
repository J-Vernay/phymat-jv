
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
        ask_camera_ui(camera);
        spawner.ask_ui();

        // Finalizes GUI and show drawings to screen.
        window.end_frame();
    }


    return 0;
}