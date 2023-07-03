#include "Joint.hpp"
#include "Spring.hpp"

#include <GL/glut.h>
#include <GLFW/glfw3.h>


/*-------------------------------------------------------------------*/
/* Render and main update                                            */
/*-------------------------------------------------------------------*/


void Joint::update(double dt) { 
    calculateForceOnJoint(dt);
    boundaryCheck();
    updateAcceleration(dt);
    updateVelocity(dt);
    updatePosition(dt);
}


void Joint::render() {
    glPushMatrix();
    glTranslatef(x / boundary.conversion, y / boundary.conversion, 0.0f);

    glBegin(GL_TRIANGLE_FAN);

    glColor3f(red, green, blue);

    // Drawing of the particle
    for (int i = 0; i <= numSegments; ++i) {
        double angle = i * theta;
        double xPos = (radius / boundary.conversion) * cos(angle);
        double yPos = (radius / boundary.conversion) * sin(angle);
        glVertex2f(xPos, yPos);
    }
    glEnd();
    glPopMatrix(); 
}


/*-------------------------------------------------------------------*/
/* Joint physics                                                     */
/*-------------------------------------------------------------------*/


void Joint::updatePosition(double dt) {
    x += (vx * dt) + (0.5 * ax * dt * dt);
    y += (vy * dt) + (0.5 * ay * dt * dt);
}


void Joint::updateVelocity(double dt) {
    vx += ax * dt;
    vy += ay * dt;
}


void Joint::updateAcceleration(double dt) {
    ax = (fx) / mass;
    ay = (fy + fg + fr) / mass;
}


bool Joint::hitBoundaryY() {  
    if (y - radius <= boundary.bottom) {
        y = boundary.bottom + radius;
        return true;

    } else if (y + radius >= boundary.top) {
        y = boundary.top - radius;
        return true;
    }
    return false;
}


bool Joint::hitBoundaryX() {
    if (x - radius <= boundary.left) {
        x = boundary.left + radius;
        return true;

    } else if (x + radius >= boundary.right) {
        x = boundary.right - radius;
        return true;

    }
    return false;
}


void Joint::boundaryCheck() {
    if (hitBoundaryX()) {
        fx = -fx;
    }
    if (hitBoundaryY()) {
        if (fy + fg < 0.0) {
            fr = -(fy + fg);
        } else {
            fr = 0.0;
        }
    }
}


void Joint::calculateForceOnJoint(double dt) {
    fx = 0.0;
    fy = 0.0;
    
    for (auto& spring : springs) {
        double springLength = spring->getLength();
        double force = spring->calculateSpringForce();

        fx += force * (spring->getDeltaX() / springLength);
        fy += force * (spring->getDeltaY() / springLength);
    }
}


/*-------------------------------------------------------------------*/
/* Getters                                                           */
/*-------------------------------------------------------------------*/


double Joint::getMass() const {
    return mass;
}


int Joint::getID() const {
    return id;
}


double Joint::getX() const {
    return x;
}


double Joint::getY() const {
    return y;
}


double Joint::getVX() const {
    return vx;
}


double Joint::getVY() const {
    return vy;
}


/*-------------------------------------------------------------------*/
/* Setters                                                           */
/*-------------------------------------------------------------------*/


void Joint::setSpring(Spring* spring) {
    springs.push_back(spring);
}


void Joint::setGravitionalForce() {
    fg = mass * g;
}


void Joint::setX(double dx) {
    x += dx;
}

void Joint::setY(double dy) {
    y += dy;
}


/*-------------------------------------------------------------------*/