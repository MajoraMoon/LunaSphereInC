/*
    Most of these comments are for personal education purposes.
    They may not be the most logical or necessary comments, but maybe they will help someone like they help me :D
    I think, many comments that may be unnecessary are better than no comments at all. hello
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main(int argc, char const *argv[])
{
    /*
     - initializing glfw
     - Setting the Version of OpenGL to use modern features. Major-version(e.g. 2.0 -> 3.0) Minor-version(e.g. 3.0 -> 3.1)
     - Setting profile for OpenGL. The Core_Profile can use the modern features of OpenGL, no old (maybe unstable)
    */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // I honestly don't like apple and their products, but maybe it helps someone lol
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window",NULL, NULL);

    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);




/*
    Main loop to open the glfw window.
    listens to Events happening to the gflw window. For example window resizing. 
*/
while (!glfwWindowShouldClose(window))
{
    // input
    processInput(window);

    // rendering...
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
}

glfwTerminate();
    return 0;
}

/*
    Whenever the window is resized, this function is called, updating the current viewport.
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width,height);
}


// function to process input with glfw...
void processInput(GLFWwindow *window){

    // pressing the escape key closes the window
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){

        glfwSetWindowShouldClose(window, true);
    }
}