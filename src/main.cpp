#include <iostream>

#include "Matrix.hpp"

#include <GLFW/glfw3.h>

int main() {
    // Example of code using Matrixes...
    auto a = Mat22{1,2,  3,4};

    std::cout << a * 4 << " " << Matrix<1,2>{3,5} << '\n';

    for (auto& line : Matrix<3,2>{1,3,  3,5,  0,0}) {
        for (auto& value : line) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }

    // Example of code using GLFW to open a window...
    if (!glfwInit())
        throw std::runtime_error("Could not initialize GLFW");

    GLFWwindow* window = glfwCreateWindow(640, 480, "Projet Sephiroth", NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Could not open GLFW window");
    }

    // This will be called for each keyboard event.
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
        // If we pressed SPACE, close window.
        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    });

    glfwMakeContextCurrent(window);

    // Main loop, taken from https://www.glfw.org/docs/3.0/quick.html
    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        // Set the projection to orthographic between [-1,-1] to [1,1]
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1, 1, 1, -1);
        
        // Making an animated rotation.
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float)glfwGetTime() * 50, 0, 0, 1);

        // Draw a triangle.
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
        
        // Show the result to screen.
        glfwSwapBuffers(window);
        // React to events.
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

