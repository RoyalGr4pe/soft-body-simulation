#ifndef JOINT_H
#define JOINT_H

#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "Spring.hpp"
#include "physics.cpp"

float PI = 3.141593;

class Joint {
private:
    float x;
    float y;
    float mass;
    float radius;
    float vx;
    float vy;
    float ax;
    float ay;
    float fx;
    float fy;
    float aR;
    int id;
    int red = 255;
    int green = 0;
    int blue = 0;
    int numSegments = 100;
    const float theta = 2.0 * PI / numSegments;
    const float g = -9.81;
    std::vector<int> springIDs;

public:
    Joint(float initialX, float initialY, float jointMass, float jointRadius, int jointID) {
        x = initialX;
        y = initialY;
        mass = jointMass;
        radius = jointRadius;
        id = jointID;
    };

    std::vector<int> getSpringIDs() const {
        return springIDs;
    }

    void addSpring(int springID) {
        springIDs.push_back(springID);
    }

    int getMass() const {
        return mass;
    }

    int getID() const {
        return id;
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    void updatePosition(float deltaTime) {
        if (!hitBoundaryY()) {
            y += vy * deltaTime;
        }
        if (!hitBoundaryX()) {
            x += vx * deltaTime;
        }
    }

    void updateVelocity(float deltaTime) {
        vx += ax * deltaTime;
        vy += ay * deltaTime;
        updatePosition(deltaTime);
    }

    void updateAcceleration(float deltaTime) {
        ax += (fx / mass) * deltaTime;
        ay += (g + (fy / mass)) * deltaTime;
        updateVelocity(deltaTime);
    }

    bool hitBoundaryY() {
        if (y - radius <= -1.0) {
            y = -1.0 + radius;
            return true;
        } else if (y + radius >= 1.0) {
            y = 1.0 - radius;
            return true;
        }
        return false;
    }

    bool hitBoundaryX() {
        if (x - radius <= -aR) {
            x = -aR + radius;
            return true;
        } else if (x + radius >= aR) {
            x = aR - radius;
            return true;
        }
        return false;
    }

    void update(float deltaTime, float aspectRatio) {
        aR = aspectRatio;
        fx = 0.0f;
        fy = 0.0f;
        updateAcceleration(deltaTime);
    }

    void draw() {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);

        glBegin(GL_TRIANGLE_FAN);

        glColor3f(red, green, blue);

        // Drawing of the particle
        for (int i = 0; i <= numSegments; ++i) {
            float angle = i * theta;
            float xPos = radius * cos(angle);
            float yPos = radius * sin(angle);
            glVertex2f(xPos, yPos);
        }
        glEnd();
        glPopMatrix(); 
    }
};


#endif