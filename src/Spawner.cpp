#include "Spawner.hpp"
#include "imgui/imgui.h"

void Spawner::spawn_projectile() {
    // TODO: actually spawn projectile with _integrator
    std::printf("SpawnProjectile(id=%i,type=%i)\n", _id, _type);
    ++_id;
}

void Spawner::ask_ui() {

    ImGui::SetNextWindowPos({50, 200}, ImGuiCond_Once);

    if (ImGui::Begin("Projectiles", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

        ImGui::SliderInt("Type", &_type, 0, 3); // 4 different types
        if (ImGui::Button("Créer"))
            spawn_projectile();
        
        ImGui::SliderFloat("Délai auto", &_delay_s, 0.1, 2, "%.2f secondes");
        ImGui::Checkbox("Auto-créer", &_autofire);
    }
    ImGui::End();
}

void Spawner::update(double current_time) {
    if (_autofire && current_time > _next_time) {
        spawn_projectile();
        _next_time = current_time + _delay_s;
    }

}
