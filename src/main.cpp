
#include <GL/gl.h>
#include <cmath>
#include <iostream>

#include "Graphics.hpp"
#include "Phase2/ParticleContact.hpp"
#include "Phase2/BungeeCordForceGenerator.hpp"
#include "Spawner.hpp"
#include "World.hpp"
#include "Blob.hpp"
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

    //Particle p(10, Vector3(0,0,3), {}, 0.2, 1);
    //world.particleList.insert(&p);

    Blob b(world, Vector3{0,0,0}, 2, 10, 1);

    // Disable use of configuration file.
    ImGui::GetIO().IniFilename = nullptr;

    
    float blob_velocity[3] { 0, 0, 0 };

    // Main loop.
    while (!window.should_close()) {
        b.center().accumulationOfForces += Vector3(blob_velocity[0], blob_velocity[1], blob_velocity[2]);
        world.integrate();

        vector<ParticleContact> contacts;
        b.addInternalContacts(contacts);
        b.addExternalContacts(contacts, &ground, 0);
        b.addExternalContacts(contacts, &obstacle1, 0);
        b.addExternalContacts(contacts, &obstacle3, 0);
        world.resolveContacts(contacts);

        // Start drawing for this frame.
        glClearColor(0.3, 0.7, 0.9, 1);
        glEnable(GL_DEPTH_TEST);
        window.begin_frame();

        // World drawings.
        use_camera_gl(window,camera);

        // Draw springs for debug.
        glColor3f(0.3, 0.7, 0.3);
        for (auto* f : world.registerOfForces) {
            if (auto* spring = dynamic_cast<SpringForceGenerator*>(f)) {
            //if (auto* spring = dynamic_cast<BungeeCordForceGenerator*>(f)) { //FOR THE DEMO
                auto [pA,pB] = spring->getParticles();
                Vector3 posA = pA->getPosition(), posB = pB->getPosition();
                glBegin(GL_LINES);
                glVertex3f(posA.getx(), posA.gety(), posA.getz());
                glVertex3f(posB.getx(), posB.gety(), posB.getz());
                glEnd();
            }
        }

        for(auto &p : world.particleList) {
            particleRenderer.draw(*p);
        }


        // GUI drawings.
        window.begin_ui();
        ask_camera_ui(camera);
        spawner.ask_ui();

        ImGui::SetNextWindowPos({ 400,50 }, ImGuiCond_Once);
        ImGui::SetNextWindowSize({ 250,100 }, ImGuiCond_Once);
        if (ImGui::Begin("Control blob")) {
            ImGui::SliderFloat3("Applied force", blob_velocity, -1000, 1000);
            if (ImGui::Button("Reset force"))
                blob_velocity[0] = 0, blob_velocity[1] = 0, blob_velocity[2] = 0;
            if(ImGui::Button("Reset Blob"))
                b.reset(Vector3{0,0,0}, 2, 10, 1);
        }
        ImGui::End();

        window.end_ui();

        // Finalizes GUI and show drawings to screen.
        window.end_frame();
    }


    return 0;
}

