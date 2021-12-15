#include "Spawner.hpp"
#include "imgui.h"

#include <algorithm>

void Spawner::spawn_star() {
    _positions.resize(0);

    if (_star) {
        _world.rigidbodyList.erase(&*_star);
        _star.reset();
    }

    // Initial position is (0,0,2).
    Particle massCenter{_mass, Vector3(0, 0, 2), Vector3(0.6, 0.1, 0.1), 1, _damp};
    /**
     * @brief 
     * Matrice d'inertie pour une etoile
     *   x 0 0
     *   0 y 0
     *   0 0 z
     *  avec x = y = z
     * car l'etoile a une masse uniformément répartie selon les 3 axes.
     * dans nos calcules, on mutltiplie l'identité par la mass de l'objet et sa hauteur dans la direction de l'axe en question
     */
    Matrix3 inertia(_mass*0.5,0,0,0,_mass*0.5,0,0,0,_mass*0.5);
    _star.emplace(massCenter, Matrix3(_mass*0.5,0,0,0,_mass*0.5,0,0,0,_mass*0.5), _angdamp);
    _world.rigidbodyList.insert(&*_star);
    _star->addForceAtBodyPoint(_force, _applyPos);
}

void Spawner::ask_ui() {
    // Positionning window manually for the first frame.
    ImGui::SetNextWindowPos({50, 200}, ImGuiCond_Once);

    if (ImGui::Begin("Projectiles", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

        ImGui::SliderFloat("Masse", &_mass, 0.1, 100, "%.1fkg");
        ImGui::SliderFloat("Damping", &_damp, 0, 1);
        ImGui::SliderFloat("Damping angulaire", &_angdamp, 0, 1);
        ImGui::SliderFloat3("Force", (float*)&_force, -10'000, 10'000, "%.1fm/s");
        ImGui::SliderFloat3("Point d'application (local)", (float*)&_applyPos, -5, 5, "%.1fm/s");
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
        _next_time = current_time + 0.1;
    }
    if (pos.getz() < -30) {
        _world.rigidbodyList.erase(&*_star);
        _star.reset();
    }
}

void Spawner::draw(ParticleRenderer& particleRenderer) const {
    if (_star)
        _star->draw();
    for (auto& pos : _positions) {
        particleRenderer.draw(pos, Vector3(0.9, 0.4, 0.1), 0.1);
    }
}