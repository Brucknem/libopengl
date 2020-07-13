#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <iostream>
#include "lib/windowing.h"
#include <cassert>

int main(int argc, char **argv)
{
    libopengl::BaseWindow *window = new libopengl::MockWindow(4, 4, 800, 600, "LearnOpenGL");
    window->MainLoop();

    return 0;
}