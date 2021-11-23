
#include <GL/gl.h>
#include <cmath>
#include <iostream>

#include "Graphics.hpp"
#include "Phase2/ParticleContact.hpp"
#include "Phase2/BungeeCordForceGenerator.hpp"
#include "Phase3/RigidBody.hpp"
#include "Phase3/Star.hpp"
#include "Spawner.hpp"
#include "World.hpp"
#include "imgui.h"


int main() {

    Window window;
    Camera camera;
    World world;
    Spawner spawner(world);
    ParticleRenderer particleRenderer;

    // Implementing ground as a big sphere.
    Particle ground(+INFINITY, Vector3(0,0,-1000), Vector3(0.5, 0.8, 0.5), 1000, 0);
    world.particleList.insert(&ground);

    Particle obstacle1(+INFINITY, Vector3(-4, 2, 0), Vector3(0.1, 0.6, 0.1), 1.5, 0);
    world.particleList.insert(&obstacle1);
    Particle obstacle3(+INFINITY, Vector3(-7, -1, 0), Vector3(0.1, 0.6, 0.1), 2, 0);
    world.particleList.insert(&obstacle3);
    
    // Disable use of configuration file.
    ImGui::GetIO().IniFilename = nullptr;


    // Main loop.
    while (!window.should_close()) {
        world.integrate();
        spawner.update(glfwGetTime());

        // Start drawing for this frame.
        glClearColor(0.3, 0.7, 0.9, 1);
        glEnable(GL_DEPTH_TEST);
        window.begin_frame();

        // World drawings.
        use_camera_gl(window,camera);

        for(auto &p : world.particleList) {
            particleRenderer.draw(*p);
        }

        spawner.draw(particleRenderer);

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

