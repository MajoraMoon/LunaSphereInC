#ifndef WINDOW_H

#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Initialize a GLFW window.
GLFWwindow *initWindow(unsigned int width, unsigned int height, const char *title);

// Takes a Key as an input. At the moment it will only close the window.
// if called, you can only press the escape key to close the window (working on it later)
// use it in the render loop
void processKeyPressInput(GLFWwindow *window);

// Clean up all the set up, if the main while loops terminates
void cleanupWindow(GLFWwindow *window);

// does what it says, use bool (1 || 0) to activate it or not
void activateVSync(int activate);

#endif