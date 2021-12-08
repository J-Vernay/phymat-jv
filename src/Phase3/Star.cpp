#include "Star.hpp"

#include "../Graphics.hpp"
#include <GL/gl.h>

static constexpr GLfloat _extrusion = 5;

static GLfloat _starVertices[30][3] = {
    // Face Z- (i = 0)
    {0, 0, -_extrusion}, {-1, -1, -1}, {-1, 1, -1}, {1, 1, -1}, {1, -1, -1},
    // Face Z+ (i = 5)
    {0, 0, _extrusion}, {-1, -1, 1}, {-1, 1, 1}, {1, 1, 1}, {1, -1, 1},
    // Face X- (i = 10)
    {-_extrusion, 0, 0}, {-1, -1, -1}, {-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1}, 
    // Face X+ (i = 15)
    {_extrusion, 0, 0}, {1, -1, -1}, {1, -1, 1}, {1, 1, 1}, {1, 1, -1}, 
    // Face Y- (i = 20)
    {0, -_extrusion, 0}, {-1, -1, -1}, {-1, -1, 1}, {1, -1, 1}, {1, -1, -1}, 
    // Face Y+ (i = 25)
    {0, _extrusion, 0}, {-1, 1, -1}, {-1, 1, 1}, {1, 1, 1}, {1, 1, -1}, 
};

static GLubyte _starIndices[] = {
     0, 1, 2,   0, 2, 3,   0, 3, 4,   0, 4, 1, // Face Z-
     5, 6, 7,   5, 7, 8,   5, 8, 9,   5, 9, 6, // Face Z+
    10,11,12,  10,12,13,  10,13,14,  10,14,11, // Face X-
    15,16,17,  15,17,18,  15,18,19,  15,19,16, // Face X+
    20,21,22,  20,22,23,  20,23,24,  20,24,21, // Face Y-
    25,26,27,  25,27,28,  25,28,29,  25,29,26, // Face Y+
};

void Star::draw() const {
    glPushMatrix();
    auto p = getMassCenter();
    glTranslatef(p.getPosition().getx(),p.getPosition().gety(),p.getPosition().getz());

    /*auto angPos = getAngularPosition();       //old without quaternion
    auto angle = angPos.norm();
    glRotatef(angle, angPos.getx(), angPos.gety(), angPos.getz());*/

    auto q = getOrientation();
    q.normalize();
    auto angle = acos(q.getW())*180/3.14;
    auto axis = q.getImaginaryNumbers();
    glRotatef(angle, asin(axis.getx())*180/3.14, asin(axis.gety())*180/3.14, asin(axis.getz())*180/3.14);
    
    auto scale = p.getRadius() / _extrusion;
    glScalef(scale, scale, scale);

    Vector3 color = p.getColor();
    glColor3f(color.getx(), color.gety(), color.getz());
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, _starVertices);
    // First as polygon,
    glDrawElements(GL_TRIANGLES, sizeof(_starIndices), GL_UNSIGNED_BYTE, _starIndices);
    // Then as wireframe
    glColor3f(0, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2);
    glDrawElements(GL_TRIANGLES, sizeof(_starIndices), GL_UNSIGNED_BYTE, _starIndices);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}