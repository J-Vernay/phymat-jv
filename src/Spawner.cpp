#include "Spawner.hpp"
#include "imgui.h"

#include <algorithm>
#include <bits/ranges_algo.h>

void Spawner::spawn_particle() {
    if (_particles.size() >= MaxParticles)
        return; /// Cannot spawn particle, already full.
    
    // Initial position is (0,0,2).
    _particles.push_back(Particle(_mass, Vector3(0,0,2), /*color*/{}, /*radius*/0.5f, _damp));
    _particles.back().setVelocity(_velocity);
    _integrator.particleList.insert(&_particles.back());
}

void Spawner::ask_ui() {
    // Positionning window manually for the first frame.
    ImGui::SetNextWindowPos({50, 200}, ImGuiCond_Once);

    if (ImGui::Begin("Projectiles", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

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
    // Should we spawn a new bullet?
    if (_autofire && current_time > _next_time) {
        spawn_particle();
        _next_time = current_time + _delay_s;
    }
    // Remove particles which are deep below ground.
    auto new_end = std::remove_if(_particles.begin(), _particles.end(), [](Particle const& p) {
        return p.getPosition().getz() < -5;
    });
    for (auto it = new_end; it != _particles.end(); ++it) {
        _integrator.particleList.erase(&*it);
    }
    _particles.erase(new_end, _particles.end());
}
