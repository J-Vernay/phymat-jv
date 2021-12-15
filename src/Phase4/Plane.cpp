#include "Plane.hpp"
#include "Octree.hpp"
#include "../Graphics.hpp"
#include <GL/gl.h>

Vector3 Plane::getNormale() const {
	switch(normale) {
	case Normale::Xm: return {-1, 0, 0};
	case Normale::Xp: return {+1, 0, 0};
	case Normale::Ym: return {0, -1, 0};
	case Normale::Yp: return {0, +1, 0};
	case Normale::Zm: return {0, 0, -1};
	case Normale::Zp: return {0, 0, +1};
	default: return {0, 0, 0};
	}
}

void Plane::setNormale(Normale newNormale) {
	normale = newNormale;
}

float Plane::getOffset() const {
	return offset;
}

void Plane::setOffset(float newOffset) {
	offset = newOffset;
}

BoundingBox Plane::getBoundingBox() const {
	Vector3 normale = getNormale();
	Vector3 center = normale * offset;
	Vector3 halfsize = {
		(normale.getx() == 0) * size + 0.1f,
		(normale.gety() == 0) * size + 0.1f,
		(normale.getz() == 0) * size + 0.1f,
	};
	return {center, halfsize};
}

void Plane::draw() const {
    glPushMatrix();
	Vector3 pos = getNormale() * offset;
	glTranslatef(pos.getx(), pos.gety(), pos.getz());
    glColor3f(color.getx(), color.gety(), color.getz());
	glBegin(GL_TRIANGLE_FAN);
	switch (normale) {
	case Normale::Xm: case Normale::Xp:
		glVertex3f(0, -size, -size);
		glVertex3f(0, -size, size);
		glVertex3f(0, size, size);
		glVertex3f(0, size, -size);
		break;
	case Normale::Ym: case Normale::Yp:
		glVertex3f(-size, 0, -size);
		glVertex3f(-size, 0, size);
		glVertex3f(size, 0, size);
		glVertex3f(size, 0, -size);
		break;
	case Normale::Zm: case Normale::Zp:
		glVertex3f(-size, -size, 0);
		glVertex3f(-size, size, 0);
		glVertex3f(size, size, 0);
		glVertex3f(size, -size, 0);
		break;
	}
	glEnd();
	glPopMatrix();
}