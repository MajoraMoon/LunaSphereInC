/*
    Most of these comments are for personal education purposes.
    They may not be the most logical or necessary comments, but maybe they will help someone like they help me :D
    I think, many comments that may be unnecessary are better than no comments at all. hello
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

double lastTime = 0.0;
int frames = 0;

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

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window", NULL, NULL);

    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); // V-Sync enabled

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

// set up shaders..
// handling windows weird way to describe filepaths..
#ifdef _WIN32

    Shader shader = createShader("../shader/shader.vert", "../shader/shader.frag");

#else
    // the lovely way!
    Shader shader = createShader("src/shader/shader.vert", "src/shader/shader.frag");

#endif

    // setting up vertex data
    float vertices[] = {
        // color values added (RGB)
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top

    };

    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // shows the Forms in Wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /*
        Main loop to open the glfw window.
        listens to Events happening to the gflw window. For example window resizing.

    */
    glBindVertexArray(VAO);

    while (!glfwWindowShouldClose(window))
    {

        // counts and prints Frames per second
        double currentTime = glfwGetTime();
        frames++;
        if (currentTime - lastTime >= 1.0)
        {
            printf("FPS: %d\n", frames);
            frames = 0;
            lastTime = currentTime;
        }

        // input
        processInput(window);

        // rendering...
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        useShader(&shader);

        double timeValue = glfwGetTime();
        float greenValue = (float)(sin(timeValue) / 2.0 + 0.5);
        int vertexColorLocation = glGetUniformLocation(shader.ID, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // render the triangle...
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    deleteShader(&shader);

    glfwTerminate();
    return 0;
}

/*
    Whenever the window is resized, this function is called, updating the current viewport.
*/
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// function to process input with glfw...
void processInput(GLFWwindow *window)
{

    // pressing the escape key closes the window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {

        glfwSetWindowShouldClose(window, true);
    }
}