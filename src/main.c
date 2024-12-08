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
#include "window.h"
#include "fps.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// settings

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

double lastTime = 0.0;
int frames = 0;

int main(int argc, char const *argv[])
{
    // setting up a window with GLFW
    GLFWwindow *window = initWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL window", 1);

    // set up shaders..
    Shader shader = createShader("../shader/shader.vert", "../shader/shader.frag");

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

        calculateAndPrintFPS();

        // input
        processKeyPressInput(window);

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

        updateWindow(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    deleteShader(&shader);

    cleanupWindow(window);
    return 0;
}
