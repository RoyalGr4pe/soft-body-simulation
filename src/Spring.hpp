#ifndef SPRING_H
#define SPRING_H

#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#include "Joint.hpp"

class Spring {
private:
    float length = 0.06;
    float x1;
    float y1;
    float x2;
    float y2;
    float k;
    float id;
    int j1ID;
    int j2ID;
    Joint* j1;
    Joint* j2;

public:
    Spring(float initialX1, float initialY1, float initialX2, float initialY2, float springConstant, Joint* joint1, Joint* joint2, int springID) {
        x1 = initialX1;
        y1 = initialY1;
        x2 = initialX2;
        y2 = initialY2;
        k = springConstant;
        id = springID;
        j1 = joint1;
        j2 = joint2;
        j1ID = j1->getID();
        j2ID = j2->getID();
    };

    int getID() const {
        return id;
    }

    int getJoint1ID() const {
        return j1ID;
    }

    int getJoint2ID() const {
        return j2ID;
    }

    void update() {
        x1 = j1->getX();
        x2 = j2->getX();
        y1 = j1->getY();
        y2 = j2->getY();
    }

    void draw() {
        glColor3f(1.0f, 1.0f, 1.0f);

        glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0f);

        glBegin(GL_LINES);

            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        
        glEnd();
        glPopMatrix();   
    }
};

#endif