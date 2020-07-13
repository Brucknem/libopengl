#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <iostream>
#include "lib/windowing.h"
#include "lib/shader.h"
#include "lib/opengl_object_3d.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    libopengl::BaseWindow *window = new libopengl::BaseWindow(4, 4, 800, 600, "LearnOpenGL");

    libopengl::Shader* vertexFragmentShader = new libopengl::VertexFragmentShader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<float> vertices = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    std::vector<unsigned int> indices = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    libopengl::OpenGLObject3D* square = new libopengl::OpenGLObject3D(vertices, indices, 3, GL_FLOAT, int(3 * sizeof(float)), 0); 

    while (!glfwWindowShouldClose(window->window))
    {
        // input
        // -----
        processInput(window->window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        
        vertexFragmentShader->Activate();
        square->Render();

        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}