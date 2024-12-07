#include <stdio.h>
#include <GLFW/glfw3.h>

#include "fps.h"

void calculateAndPrintFPS()
{
    static double lastTime = 0.0;
    static int frames = 0;

    double currentTime = glfwGetTime();
    frames++;
    if (currentTime - lastTime >= 1.0)
    {
        printf("FPS: %d\n", frames);
        frames = 0;
        lastTime = currentTime;
    }
}