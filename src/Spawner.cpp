#include "Spawner.hpp"
#include "imgui/imgui.h"

void Spawner::spawn_projectile(float mass,Vector3 initPos, Vector3 initVel, float damp) {
    // TODO: actually spawn projectile with _integrator
    std::printf("SpawnProjectile(id=%i,type=%i)\n", _id, _type);
    ++_id;

    _integrator.addParticle(Particle(mass,initPos, initVel, _accel, damp));
}

void Spawner::ask_ui() {

    ImGui::SetNextWindowPos({50, 200}, ImGuiCond_Once);

    if (ImGui::Begin("Projectiles", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

        ImGui::SliderInt("Type", &_type, 0, 3); // 4 different types
        ImGui::SliderFloat3("Accélération", (float*)&_accel, 0, 10);
        if (ImGui::Button("Créer"))
            spawn_projectile(-1, Vector3(0,0,5), Vector3(0,0,0), 1);
        
        ImGui::SliderFloat("Délai auto", &_delay_s, 0.1, 2, "%.2f secondes");
        ImGui::Checkbox("Auto-créer", &_autofire);

    }
    ImGui::End();
}

void Spawner::update(double current_time) {
    if (_autofire && current_time > _next_time) {
        spawn_projectile(-1, Vector3(0,0,5), Vector3(0,0,0), 1);
        _next_time = current_time + _delay_s;
    }

}
