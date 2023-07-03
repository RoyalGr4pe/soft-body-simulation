#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
using namespace std;

#include "src/Spring.hpp"
#include "src/Joint.hpp"
#include "src/create_objects.cpp"

//https://www.pdf.inf.usi.ch/papers/bachelor_projects/jacob_salvi.pdf


bool isRunning = true;  // Flag to control the program loop


void windowCloseCallback(GLFWwindow* window) {
    isRunning = false;  // Set the flag to false when the window is closed
}

struct ProgramState {
    double prevTime;
    double speed;
};

void updateJointsAndSprings(std::vector<std::vector<Joint*>>& joints, std::vector<Spring*>& springs, double dt) {
    for (auto& row : joints) {
        for (auto& joint : row) {
            joint->update(dt);
        }
    }
    for (auto& spring : springs) {
        spring->update();
    }
}

void renderJointsAndSprings(std::vector<std::vector<Joint*>>& joints, std::vector<Spring*>& springs) {
    for (auto& spring : springs) {
        spring->render();
    }
    for (auto& row : joints) {
        for (auto& joint : row) {
            joint->render();
        }
    }
}

void display(GLFWwindow* window, int width, int height, ProgramState& state, std::vector<std::vector<Joint*>>& joints, std::vector<Spring*>& springs) {
    glTranslatef(0.0, 0.0, 1.0); // Translate to center of screen

    while (isRunning) {  // Check the flag to continue running the program
        glfwGetWindowSize(window, &width, &height);

        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

        double currentTime = glfwGetTime();  // Get the current frame time
        double dt = state.speed * (currentTime - state.prevTime);  // Calculate the time difference

        updateJointsAndSprings(joints, springs, dt);
        renderJointsAndSprings(joints, springs);

        state.prevTime = currentTime;  // Update the previous time

        glFlush();
        glfwSwapBuffers(window);  // Swap the front and back buffers

        glfwPollEvents();  // Poll for events
    }
}


void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_PROJECTION);
    double aspect = (double)width / (double)height;
    glOrtho(-aspect, aspect, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char** argv) {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    const double initialWidth = 1920.0f;
    const double initialHeight = 1080.0f;
    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(initialWidth, initialHeight, "Soft Body Simulator", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    // Set the window context
    glfwMakeContextCurrent(window);

    // Register the window close callback function
    glfwSetWindowCloseCallback(window, windowCloseCallback);

    // Set the viewport and projection matrix
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    reshape(width, height);
    double aspectRatio = (double)width/(double)height;
    
    int rgbRed = 42;
    int rgbGreen = 75;
    int rgbBlue = 95;

    
    // Background colour
    glClearColor(rgbRed/256.0, rgbGreen/256.0, rgbBlue/256.0, 1.0f);

    ProgramState state;
    state.prevTime = glfwGetTime();
    state.speed = 2.0f;

    const int numberOfJoints = 4;

    std::vector<std::vector<Joint*>> joints = createJoints(numberOfJoints);
    std::vector<Spring*> springs = createSprings(joints);

    while (!glfwWindowShouldClose(window)) {
        display(window, width, height, state, joints, springs);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}