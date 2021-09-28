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
        integrator.updateAll();

        glClearColor(0.3, 0.7, 0.9, 1);

        window.begin_frame();
        use_camera_gl(window,camera);


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

        
        for(auto &p : integrator.getParticleList()){
            std::printf("\033c");
            std::cout<<p<<std::endl;
            glPushMatrix();
            glTranslatef(p.getPosition().getx(),p.getPosition().gety(),p.getPosition().getz());
            Projectile* bullet = new Projectile();
            bullet->draw(p.getType());
            glPopMatrix();
        }

        ask_camera_ui(camera);
        spawner.ask_ui();


        window.end_frame();
    }


    return 0;
}
