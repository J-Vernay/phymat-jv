#include "Spawner.hpp"
#include "imgui.h"

#include <algorithm>
#include <bits/ranges_algo.h>

void Spawner::spawn_star() {
    _positions.resize(0);

    if (_star) {
        _world.rigidbodyList.erase(&*_star);
        _star = {};
    }

    // Initial position is (0,0,2).
    Particle massCenter{_mass, Vector3(0, 0, 2), Vector3(0.6, 0.1, 0.1), 1, _damp};
    massCenter.setVelocity(_velocity);
    RigidBody rigidBody{massCenter, Matrix3::identity(), _angdamp};
    _star = Star{rigidBody};
    _world.rigidbodyList.insert(&*_star);
}

void Spawner::ask_ui() {
    // Positionning window manually for the first frame.
    ImGui::SetNextWindowPos({50, 200}, ImGuiCond_Once);

    if (ImGui::Begin("Projectiles", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

        ImGui::SliderFloat("Masse", &_mass, 0.1, 100, "%.1fkg");
        ImGui::SliderFloat("Damping", &_damp, 0, 1);
        ImGui::SliderFloat("Damping angulaire", &_angdamp, 0, 1);
        ImGui::SliderFloat3("Vélocité", (float*)&_velocity, -10, 10, "%.1fm/s");
        ImGui::SliderFloat("Délai entre points", &_delay_s, 0, 1);
        if (ImGui::Button("Créer"))
            spawn_star();
    }
    ImGui::End();
}


void Spawner::update(double current_time) {
    
    if (!_star) return;

    auto pos = _star->getMassCenter().getPosition();
    // Should we store the current position of mass center?
    if (current_time > _next_time) {
        _positions.push_back(pos);
        _next_time = current_time + _delay_s;
    }
    if (pos.getz() < -5) {
        _world.rigidbodyList.erase(&*_star);
        _star = {};
    }
}

void Spawner::draw() {
    if (_star)
        _star->draw();
}