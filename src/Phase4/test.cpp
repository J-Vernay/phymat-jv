#include "Plane.h"
#include "../World.hpp"
#include "../Vector.hpp"
#include "../Phase3/Matrix3.hpp"
#include "../Particle.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    World w = World();
    Particle part = Particle(1, Vector3(0,0,0), Vector3(255,255,255), 1, 0);
    Plane p = Plane(part, Matrix3(1,0,0,0,1,0,0,0,1), 0, Vector3(1,1,0), 0);
    Vector3 dist = Vector3(1,0,0);

    cout << w.getDistanceFromTheWall(&p,dist) << endl;

    return 0;
}
