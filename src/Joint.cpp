#include "Joint.hpp"
#include "Spring.hpp"

#include <GL/glut.h>
#include <GLFW/glfw3.h>


void Joint::addSpring(Spring* spring) {
    springs.push_back(spring);
}

void Joint::setXBoundary(double aspectRatio) {
    aR = aspectRatio;
}

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

void Joint::calculateForceOnJoint(double deltaTime) {
    for (auto& spring : springs) {
        double springLength = spring->getLength();
        double force = spring->getSpringForce();

        if (springLength != 0.0) {
            fx += force * deltaTime * (spring->getDeltaX() / springLength);
            fy += force * deltaTime * (spring->getDeltaY() / springLength);
        }
    }
}

void Joint::updatePosition(double deltaTime) {
    x += vx * deltaTime;
    y += vy * deltaTime;
}

void Joint::updateVelocity(double deltaTime) {
    vx += ax * deltaTime;
    vy += ay * deltaTime;
}

void Joint::updateAcceleration(double deltaTime) {
    ax += (fx / mass) * deltaTime;
    ay += (g + (fy / mass)) * deltaTime;
}

bool Joint::hitBoundaryY() {
    if (y - radius <= -1.0) {
        y = -1.0 + radius;
        return true;
    } else if (y + radius >= 1.0) {
        y = 1.0 - radius;
        return true;
    }
    return false;
}

bool Joint::hitBoundaryX() {
    if (x - radius <= -aR) {
        x = -aR + radius;
        return true;
    } else if (x + radius >= aR) {
        x = aR - radius;
        return true;
    }
    return false;
}

void Joint::boundaryCheck() {
    if (hitBoundaryX()) {
        vx = 0.0f;
        ax = 0.0f;
    }
    if (hitBoundaryY()) {
        vy = 0.0f;
        ay = 0.0f;
    }
}

void Joint::update(double deltaTime) {
    boundaryCheck();
    calculateForceOnJoint(deltaTime);
    updateAcceleration(deltaTime);
    updateVelocity(deltaTime);
    updatePosition(deltaTime);
}

void Joint::render() {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glBegin(GL_TRIANGLE_FAN);

    glColor3f(red, green, blue);

    // Drawing of the particle
    for (int i = 0; i <= numSegments; ++i) {
        double angle = i * theta;
        double xPos = radius * cos(angle);
        double yPos = radius * sin(angle);
        glVertex2f(xPos, yPos);
    }
    glEnd();
    glPopMatrix(); 
}