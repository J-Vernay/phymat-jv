#include <cmath>
#include <iostream>

#include "Graphics.hpp"
#include "Phase2/ParticleContact.hpp"
#include "Phase2/BungeeCordForceGenerator.hpp"
#include "Phase3/RigidBody.hpp"
#include "Phase3/Star.hpp"
#include "Phase4/Plane.hpp"
#include "Spawner.hpp"
#include "World.hpp"
#include "imgui.h"


int main() {

    World world;
    Window window;
    Camera camera;
    Spawner spawner(world);
    ParticleRenderer particleRenderer;

    Particle wallbase(+INFINITY, {}, {}, {}, {});
    Vector3 wallcolor{0.3, 0.5, 0.3};
    float offset = 10;
    float size = 10;

    Plane planes[] {
        {wallbase, Matrix3::identity(), 0, Plane::Xm, offset, size, {0.5, 0.2, 0.2}},
        {wallbase, Matrix3::identity(), 0, Plane::Xp, offset, size, {0.5, 0.2, 0.2}},
        {wallbase, Matrix3::identity(), 0, Plane::Ym, offset, size, {0.2, 0.5, 0.2}},
        {wallbase, Matrix3::identity(), 0, Plane::Yp, offset, size, {0.2, 0.5, 0.2}},
        {wallbase, Matrix3::identity(), 0, Plane::Zm, offset, size, {0.2, 0.2, 0.5}},
        {wallbase, Matrix3::identity(), 0, Plane::Zp, offset, size, {0.2, 0.2, 0.5}},
    };

    for (auto& plane : planes)
        world.rigidbodyList.insert(&plane);
    
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

        for (Plane const& plane : planes) {
            plane.draw();
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

