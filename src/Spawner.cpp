#include "Spawner.hpp"
#include "imgui/imgui.h"

void Spawner::spawn_particle() {
    // Initial position is (0,0,2).
    _integrator.addParticle(Particle(_mass, Vector3(0,0,2), _velocity, Vector3(0,0,0), _damp, _type));
}

void Spawner::ask_ui() {
    // Positionning window manually for the first frame.
    ImGui::SetNextWindowPos({50, 200}, ImGuiCond_Once);

    if (ImGui::Begin("Projectiles", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

        ImGui::SliderInt("Type", &_type, 0, 1); // 2 different types
        ImGui::SliderFloat("Masse", &_mass, 0.1, 100, "%.1fkg");
        ImGui::SliderFloat("Damping", &_damp, 0, 1);
        ImGui::SliderFloat3("Vélocité", (float*)&_velocity, -10, 10, "%.1fm/s");
        if (ImGui::Button("Créer"))
            spawn_particle();
        
        ImGui::SliderFloat("Délai auto", &_delay_s, 0.1, 2, "%.2f secondes");
        ImGui::Checkbox("Auto-créer", &_autofire);

    }
    ImGui::End();
}

void Spawner::update(double current_time) {
    // should we spawn a new bullet?
    if (_autofire && current_time > _next_time) {
        spawn_particle();
        _next_time = current_time + _delay_s;
    }

}
