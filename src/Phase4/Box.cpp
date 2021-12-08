#include "Box.h"

Box::Box(Vector3 newHalfsizes) {
	halfsizes = newHalfsizes;
};

Vector3 Box::getHalfsizes() {
	return halfsizes;
};
void Box::setHalfsizes(Vector3 newHalfsizes) {
	halfsizes = newHalfsizes;
};