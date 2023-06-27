#ifndef JOINT_H
#define JOINT_H

#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <math.h>

// Forward Deceleration to avoid circular import error
// https://stackoverflow.com/questions/625799/resolve-build-errors-due-to-circular-dependency-amongst-classes
class Spring; 


class Joint {
private:
    double x;
    double y;
    double mass;
    double radius;
    double vx;
    double vy;
    double ax;
    double ay;
    double fx;
    double fy;
    double aR;
    int id;
    int red = 255;
    int green = 0;
    int blue = 0;
    int numSegments = 100;
    double PI = 3.141593;
    const double theta = 2.0 * PI / numSegments;
    const double g = -9.81;
    std::vector<Spring*> springs;

public:
    Joint(double initialX, double initialY, double jointMass, double jointRadius, int jointID) {
        x = initialX;
        y = initialY;
        mass = jointMass;
        radius = jointRadius;
        id = jointID;
    };
    void addSpring(Spring* spring);
    double getMass() const;
    int getID() const;
    double getX() const;
    double getY() const;
    void calculateForceOnJoint();
    void boundaryCheck();
    void updatePosition(double deltaTime);
    void updateVelocity(double deltaTime);
    void updateAcceleration(double deltaTime);
    bool hitBoundaryY();
    bool hitBoundaryX();
    void update(double deltaTime, double aspectRatio);
    void draw();
};


#endif