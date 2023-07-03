#ifndef JOINT_H
#define JOINT_H

#include "Boundary.hpp"

#include <iostream>
#include <vector>
#include <math.h>

// Forward Deceleration to avoid circular import error
// https://stackoverflow.com/questions/625799/resolve-build-errors-due-to-circular-dependency-amongst-classes
class Spring; 


class Joint {
private:
    double mass;
    double radius;
    double x;
    double y;
    double vx = 0.0;
    double vy = 0.0;
    double ax = 0.0;
    double ay = 0.0;
    double fx;
    double fy;
    double fr = 0.0;
    double fg;
    double aR;
    int id;
    int red = 255;
    int green = 0;
    int blue = 0;
    int numSegments = 100;
    static constexpr double PI = 3.141593;
    const double theta = 2.0 * PI / numSegments;
    const double g = -9.81;
    std::vector<Spring*> springs;
    boundaryCoordinates boundary;

public:
    Joint(double initialX, double initialY, double jointMass, double jointRadius, int jointID) {
        x = initialX;
        y = initialY;
        mass = jointMass;
        radius = jointRadius;
        id = jointID;
    };
    void update(double dt);
    void render();

    void boundaryCheck();
    void calculateForceOnJoint(double dt);
    void updatePosition(double dt);
    void updateVelocity(double dt);
    void updateAcceleration(double dt);
    bool hitBoundaryY();
    bool hitBoundaryX();

    int getID() const;
    double getMass() const;
    double getX() const;
    double getY() const;
    double getVX() const;
    double getVY() const;

    void setGravitionalForce();
    void setSpring(Spring* spring);
    void setX(double dx);
    void setY(double dy);
};


#endif