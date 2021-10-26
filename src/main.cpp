
#include <GL/gl.h>
#include <cmath>
#include <iostream>

#include "Graphics.hpp"
#include "Spawner.hpp"
#include "World.hpp"
#include "Blob.hpp"

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
    World world;
    Spawner spawner(world);
    ParticleRenderer particleRenderer;

    Blob b(world, Vector3{0,0,0.2}, 1, 20, +INFINITY);

    // Disable use of configuration file.
    ImGui::GetIO().IniFilename = nullptr;

    // Main loop.
    while (!window.should_close()) {
        spawner.update(glfwGetTime()); 
        world.integrate();


        // Start drawing for this frame.
        glClearColor(0.3, 0.7, 0.9, 1);
        glEnable(GL_DEPTH_TEST);
        window.begin_frame();

        // World drawings.
        use_camera_gl(window,camera);
        draw_floor();

        for (auto* f : world.registerOfForces) {
            if (auto* spring = dynamic_cast<SpringForceGenerator*>(f)) {
                auto [pA,pB] = spring->getParticles();
                Vector3 posA = pA->getPosition(), posB = pB->getPosition();
                glBegin(GL_LINES);
                glVertex3f(posA.getx(), posA.gety(), posA.getz());
                glVertex3f(posB.getx(), posB.gety(), posB.getz());
                glEnd();
            }
        }

        for(auto &p : world.particleList) {
            // Draw each particle according to its type.
            glPushMatrix();
            glTranslatef(p->getPosition().getx(),p->getPosition().gety(),p->getPosition().getz());
            particleRenderer.draw(*p);
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

