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

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

double lastTime = 0.0;
int frames = 0;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

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
    // vertex shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // check for compiling shader errors..
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }

    // fragment shaders
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    // check for compiling shader errors.. (fragment)
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }

    // shader Programm, it links the compiled shaders together..
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // setting up vertex data
    float verticesFirstTriangle[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f, // bottom left
        -0.0f, -0.5f, 0.0f, // bottom right
        -0.45f, 0.5f, 0.0f, // top
    };

    float verticesSecondTriangle[] = {
        0.0f, -0.5f, 0.0f,
        0.9f, -0.5f, 0.0f,
        0.45f, 0.5f, 0.0f

    };

    unsigned int VBOs[2], VAOs[2];

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // Bind first triangle
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFirstTriangle), verticesFirstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); // Vertex attributes stay the same
    glEnableVertexAttribArray(0);

    // bind second triangle
    glBindVertexArray(VAOs[1]);             // note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSecondTriangle), verticesSecondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);

    // shows the Forms in Wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /*
        Main loop to open the glfw window.
        listens to Events happening to the gflw window. For example window resizing.

    */

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

        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, VAOs);
    glDeleteBuffers(1, VBOs);
    glDeleteProgram(shaderProgram);

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
