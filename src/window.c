#include <stdio.h>
#include <stdbool.h>

#include "window.h"

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow *initWindow(unsigned int width, unsigned int height, const char *title)
{
    // initializing glfw
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return NULL;
    }
    /*
     - Setting the Version of OpenGL to use modern features. Major-version(e.g. 2.0 -> 3.0) Minor-version(e.g. 3.0 -> 3.1)
     - Setting profile for OpenGL. The Core_Profile can use the modern features of OpenGL, no old (maybe unstable)
    */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // I honestly don't like apple and their products, but maybe it helps someone lol
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return NULL;
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

void processKeyPressInput(GLFWwindow *window)
{
    // pressing the escape key closes the window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void cleanupWindow(GLFWwindow *window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void activateVSync(int activate)
{
    glfwSwapInterval(activate);
}