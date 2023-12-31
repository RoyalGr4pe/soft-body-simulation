#ifndef SPRING_H
#define SPRING_H

#include "Boundary.hpp"

#include <iostream>
#include <math.h>

// Forward Deceleration to avoid circular import error
// https://stackoverflow.com/questions/625799/resolve-build-errors-due-to-circular-dependency-amongst-classes
class Joint;


class Spring {
private:
    double restingLength;
    double minimumLength = 1.0;
    double length;
    double x1;
    double y1;
    double x2;
    double y2;
    double k;
    double id;
    int j1ID;
    int j2ID;
    Joint* j1;
    Joint* j2;
    boundaryCoordinates boundary;

public:
    Spring(double initialX1, double initialY1, double initialX2, double initialY2, double springConstant, Joint* joint1, Joint* joint2, int springID, double initialLength) {
        x1 = initialX1;
        y1 = initialY1;
        x2 = initialX2;
        y2 = initialY2;
        k = springConstant;
        id = springID;
        j1 = joint1;
        j2 = joint2;
        restingLength = initialLength;
    };
    void update();
    void render();

    void updateLength();
    double calculateSpringForce();

    double getDeltaX();
    double getDeltaY();
    double getLength();
    double getRestingLength();
    double getMinimumLength();
    double getTest();
    int getID() const;
    int getJoint1ID() const;
    int getJoint2ID() const;

    void setJointIDs();
    void setSpringLength(double newLength);
};

#endif