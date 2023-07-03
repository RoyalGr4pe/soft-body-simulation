#ifndef BOUNDARY_H
#define BOUNDARY_H


struct boundaryCoordinates {
    float left = -960.0f;
    float right = 960.0f;
    float top = 527.0f;
    float bottom = -527.0f;
    float boundaryRestitution = 0.8f;
    float conversion = 527.0f;
};


#endif