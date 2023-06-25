#include "Joint.hpp"

float getComX(Joint& j1, Joint& j2) {
    return ((j1.getMass() * j1.getX()) + (j2.getMass() * j2.getX())) / (j1.getMass() + j2.getMass());
}

float getComY(Joint& j1, Joint& j2) {
    return ((j1.getMass() * j1.getY()) + (j2.getMass() * j2.getY())) / (j1.getMass() + j2.getMass());
}