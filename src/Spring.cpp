#include "Spring.hpp"
#include "Joint.hpp"

#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>


/*-------------------------------------------------------------------*/
/* Render and main update                                            */
/*-------------------------------------------------------------------*/


void Spring::update() {
    x1 = j1->getX();
    y1 = j1->getY();
    x2 = j2->getX();
    y2 = j2->getY();
    updateLength();
}


void Spring::render() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0f);

    glBegin(GL_LINES);

        glVertex2f(x1 / boundary.conversion, y1 / boundary.conversion);
        glVertex2f(x2 / boundary.conversion, y2 / boundary.conversion);
    
    glEnd();
    glPopMatrix();   
    
}

/*-------------------------------------------------------------------*/
/* Spring physics                                                    */
/*-------------------------------------------------------------------*/


void Spring::updateLength() {
    double dx = getDeltaX();
    double dy = getDeltaY();
    length = sqrt((dx * dx) + (dy * dy));
}


double Spring::calculateSpringForce() { 
    double e = length - restingLength;
    
    if (std::abs(e) < 0.00000008) {
        e = 0.0;
    }
    double force = -k * e;
    
    return force;
}


/*-------------------------------------------------------------------*/
/* Getters                                                           */
/*-------------------------------------------------------------------*/


double Spring::getDeltaX() {
    double dx = x2 - x1;
    return dx;
}


double Spring::getDeltaY() {
    double dy = y2 - y1;
    return dy;
}


double Spring::getLength() {
    double dx = getDeltaX();
    double dy = getDeltaY();
    length = sqrt((dx * dx) + (dy * dy));

    if (length == 0.0 && dx == 0.0) {
        j1->setX(minimumLength);
        x1 += minimumLength;
    } else if (length == 0.0 && dy == 0.0) {
        j1->setY(minimumLength);
        y1 += minimumLength;
    }
    updateLength();
    return length;
}


double Spring::getRestingLength() {
    return restingLength;
}


double Spring::getMinimumLength() {
    return minimumLength;
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


/*-------------------------------------------------------------------*/
/* Setters                                                           */
/*-------------------------------------------------------------------*/


void Spring::setJointIDs() {
    j1ID = j1->getID();
    j2ID = j2->getID();
}


void Spring::setSpringLength(double newLength) {
    length = newLength;
}


/*-------------------------------------------------------------------*/