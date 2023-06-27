#include "Spring.hpp"
#include "Joint.hpp"

#include <cmath>


void Spring::applyJointIDs() {
    j1ID = j1->getID();
    j2ID = j2->getID();
}

double Spring::getDeltaX() {
    double dx = x2 - x1;
    return dx;
}

double Spring::getDeltaY() {
    double dy = y2 - y1;
    return dy;
}

double Spring::getLength() {
    return length;
}

double Spring::getSpringForce() {   
    double e = length - restingLength;
    double force = -k * e;
    return force;
}

int Spring::getID() const {
    return id;
}

int Spring::getJoint1ID() const {
    return j1ID;
}

int Spring::getJoint2ID() const {
    return j2ID;
}

void Spring::updateLength() {
    double dx = getDeltaX();
    double dy = getDeltaY();
    length = sqrt((dx * dx) + (dy * dy));
    if (length < pow(1.0, -10)) {
        length = 0.0f;
    }
}

void Spring::update() {
    x1 = j1->getX();
    x2 = j2->getX();
    y1 = j1->getY();
    y2 = j2->getY();
    updateLength();
    getSpringForce();
}

void Spring::draw() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0f);

    glBegin(GL_LINES);

        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    
    glEnd();
    glPopMatrix();   
}