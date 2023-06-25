#include <vector>

#include "Spring.hpp"
#include "Joint.hpp"


bool springAlreadyAttached(std::vector<Spring> springs, Joint* joint1, Joint* joint2) {
    // Check if the spring already exists between joint1 and joint2
    for (const auto& spring : springs) {
        if ((spring.getJoint1ID() == joint1->getID() && spring.getJoint2ID() == joint2->getID())
            || (spring.getJoint1ID() == joint2->getID() && spring.getJoint2ID() == joint1->getID())) {
            return true;
        }
    }
    return false;
}

std::vector<Spring> createSprings(std::vector<std::vector<Joint>>& joints) {
    std::vector<Spring> springs;

    int springID = 1;
    for (int i = 0; i < joints.size(); i++) { 
        for (int j = 0; j < joints[i].size(); j++) {
            Joint* joint1 = &joints[i][j];
            int row = -1;
            int col = -1;
            for (int k = 1; k <= 9; k++) {
                if (!(row == 0 && col == 0) && (i + row >= 0 && i + row < joints.size()) && (j + col >= 0 && j + col < joints[i].size())) {
                    Joint* joint2 = &joints[i + row][j + col];

                    if (!springAlreadyAttached(springs, joint1, joint2)) {
                        Spring spring(joint1->getX(), joint1->getY(), joint2->getX(), joint2->getY(), 5.0f, joint1, joint2, springID);
                        springs.push_back(spring);
                        joint1->addSpring(spring.getID());
                        joint2->addSpring(spring.getID());
                        
                        springID++;
                    }
                }
                if (col < 1) {
                    col += 1;
                } else if (col == 1) {
                    col = -1;
                    row += 1;
                }
            }
        }
    }
    return springs;
}


std::vector<std::vector<Joint>> createJoints(int numJoints) {

    /*
    The number of rows and columns should be as close to each other as possible
    Such that rows * columns = numJoints
    If rows and columns can't be equal then rows should be larger then columns
    */

    int columns = sqrt(numJoints);

    // Find the closest factors
    while (numJoints % columns != 0) {
        columns--;
    }

    float rows = numJoints / columns;

    std::vector<std::vector<Joint>> jointsArray;
    
    float x0 = -0.04;
    float y0 = 0.8;
    float springLength = 0.06;

    int jointID = 1;

    for (int i = 1; i <= rows; i++) {
        std::vector<Joint> joints;
        for (int j = 1; j <= columns; j++) {
            Joint joint(x0, y0, 0.1, 0.01, jointID);
            joints.push_back(joint);
            x0 += springLength;
            jointID++;
        }
        y0 += springLength;
        x0 = -0.04;
        jointsArray.push_back(joints);
    }

    return jointsArray;
}