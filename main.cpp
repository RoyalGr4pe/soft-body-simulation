#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
using namespace std;

#include "src/Spring.hpp"
#include "src/Joint.hpp"
#include "src/create_objects.cpp"

//https://www.pdf.inf.usi.ch/papers/bachelor_projects/jacob_salvi.pdf


const float initialWidth = 1920.0f;
const float initialHeight = 1080.0f;

bool isRunning = true;  // Flag to control the program loop


void windowCloseCallback(GLFWwindow* window) {
    isRunning = false;  // Set the flag to false when the window is closed
}


void display(GLFWwindow* window, int width, int height) {
    float aspectRatio = (float)width/(float)height;

    std::vector<std::vector<Joint>> joints = createJoints(16);
    std::vector<Spring> springs = createSprings(joints);


    glTranslatef(0.0, 0.0, 1.0); // Translate to center of screen

    static float prevTime = glfwGetTime();  // Initialize prevTime with the current time

    static float speed = 0.2f;

    float flag = 0.0;


    while (isRunning) {  // Check the flag to continue running the program
        glfwGetWindowSize(window, &width, &height);

        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

        float currentTime = glfwGetTime();  // Get the current frame time
        float deltaTime = speed * (currentTime - prevTime);  // Calculate the time difference

        for (auto& row : joints) {
            for (auto& joint : row) {
                joint.update(deltaTime, aspectRatio);
            }
        } 
        for (auto& spring : springs) {
            spring.update();
            spring.draw();
        } 
        for (auto& row : joints) {
            for (auto& joint : row) {
                joint.draw();
            }
        } 



        prevTime = currentTime;  // Update the previous time

        glFlush();
        glfwSwapBuffers(window);  // Swap the front and back buffers

        glfwPollEvents();  // Poll for events
    }
}




void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_PROJECTION);
    float aspect = (float)width / (float)height;
    glOrtho(-aspect, aspect, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char** argv) {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

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
    
    int rgbRed = 42;
    int rgbGreen = 75;
    int rgbBlue = 95;

    
    // Background colour
    glClearColor(rgbRed/256.0, rgbGreen/256.0, rgbBlue/256.0, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        display(window, width, height);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}