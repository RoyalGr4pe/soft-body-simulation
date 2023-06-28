#include <vector>
#include <iostream>

#include "Spring.hpp"
#include "Joint.hpp"


bool springAlreadyAttached(std::vector<Spring*> springs, Joint* joint1, Joint* joint2) {
    // Check if the spring already exists between joint1 and joint2
    for (const auto& spring : springs) {
        if ((spring->getJoint1ID() == joint1->getID() && spring->getJoint2ID() == joint2->getID())
            || (spring->getJoint1ID() == joint2->getID() && spring->getJoint2ID() == joint1->getID())) {
            return true;
        }
    }
    return false;
}


bool isValidJointIndex(std::vector<std::vector<Joint>>& joints, int row, int col) {
    return row >= 0 && row < joints.size() && col >= 0 && col < joints[row].size();
}


std::vector<Spring*> createSprings(std::vector<std::vector<Joint>>& joints) {
    std::vector<Spring*> springs;
    
    int springID = 1;
    for (int i = 0; i < joints.size(); i++) { 
        for (int j = 0; j < joints[i].size(); j++) {
            Joint* joint1 = &joints[i][j];

            // Define relative positions of neighboring joints
            std::vector<std::pair<int, int>> neighborOffsets = {
                {-1, -1}, {-1, 0}, {-1, 1},
                {0,  -1},          {0,  1},
                {1,  -1}, {1,  0}, {1,  1}
            };

            for (const auto& offset : neighborOffsets) {
                int row = i + offset.first;
                int col = j + offset.second;
                double restingLength = 0.06;

                Joint* joint2 = &joints[row][col];

                if (isValidJointIndex(joints, row, col) && !springAlreadyAttached(springs, joint1, joint2)) {
                    // Increase the restingLength if the spring is a diagonal
                    restingLength = (offset.first == 0 || offset.second == 0) ? restingLength : sqrt(2.0 * restingLength * restingLength); 

                    Spring* spring = new Spring(joint1->getX(), joint1->getY(), joint2->getX(), joint2->getY(), .005, joint1, joint2, springID, restingLength);
                    spring->applyJointIDs();

                    joint1->addSpring(spring);
                    joint2->addSpring(spring);
                    spring->update();
                    
                    springs.push_back(spring);
                    springID++;
                }
            }
        }
    }
    return springs;
}


std::vector<std::vector<Joint>> createJoints(int numJoints, double aspectRatio) {

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
            joint.setXBoundary(aspectRatio);
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