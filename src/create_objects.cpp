#include <vector>
#include <iostream>

#include "Spring.hpp"
#include "Joint.hpp"


float springRestingLength = 50;


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


bool isValidJointIndex(std::vector<std::vector<Joint*>>& joints, int row, int col) {
    return row >= 0 && row < joints.size() && col >= 0 && col < joints[row].size();
}


std::vector<Spring*> createSprings(std::vector<std::vector<Joint*>>& joints) {
    std::vector<Spring*> springs;
    
    int springID = 1;
    for (int i = 0; i < joints.size(); i++) { 
        for (int j = 0; j < joints[i].size(); j++) {

            // Define relative positions of neighboring joints
            std::vector<std::pair<int, int>> neighborOffsets = {
                {-1, -1}, {-1, 0}, {-1, 1},
                {0,  -1},          {0,  1},
                {1,  -1}, {1,  0}, {1,  1}
            };

            for (const auto& offset : neighborOffsets) {
                int row = i + offset.first;
                int col = j + offset.second;
                double tempLength = springRestingLength;


                if (isValidJointIndex(joints, row, col) && !springAlreadyAttached(springs, joints[i][j], joints[row][col])) {
                    // Increase the restingLength if the spring is a diagonal
                    tempLength = (offset.first == 0 || offset.second == 0) ? tempLength : sqrt(2.0 * tempLength * tempLength); 
                    
                    if (tempLength == springRestingLength) {  
                        Spring* spring = new Spring(joints[i][j]->getX(), joints[i][j]->getY(), joints[row][col]->getX(), joints[row][col]->getY(), 100, joints[i][j], joints[row][col], springID, tempLength);
                        spring->setJointIDs();

                        joints[i][j]->setSpring(spring);
                        joints[row][col]->setSpring(spring);
                        spring->update();
                        
                        springs.push_back(spring);
                        springID++;
                    }
                }
            }
        }
    }
    return springs;
}


std::vector<std::vector<Joint*>> createJoints(int numberOfJoints) {

    /*
    The number of rows and columns should be as close to each other as possible
    Such that rows * columns = numJoints
    If rows and columns can't be equal then rows should be larger then columns
    */

    int columns = sqrt(numberOfJoints);

    // Find the closest factors
    while (numberOfJoints % columns != 0) {
        columns--;
    }

    float rows = numberOfJoints / columns;

    std::vector<std::vector<Joint*>> jointsArray;
    
    float x0 = -100;
    float hold_x0 = x0;
    float y0 = -400.0;
    

    int jointID = 1;

    for (int i = 1; i <= rows; i++) {
        std::vector<Joint*> joints;
        for (int j = 1; j <= columns; j++) {
            Joint* joint = new Joint(x0, y0, 10, 0.1, jointID);
            joint->setGravitionalForce();
            joints.push_back(joint);
            x0 += springRestingLength;
            jointID++;
        }
        y0 += springRestingLength;
        x0 = hold_x0;
        jointsArray.push_back(joints);
    }

    return jointsArray;
}