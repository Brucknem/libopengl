#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <iostream>
#include "lib/windowing.h"
#include "lib/shader.h"
#include "lib/opengl_object_3d.h"
#include <iostream>

int main(int argc, char **argv)
{
    libopengl::BaseWindow *window = new libopengl::BaseWindow(4, 4, 800, 600, "LearnOpenGL");

    libopengl::Shader* vertexFragmentShader = new libopengl::VertexFragmentShader("shaders/vertex.glsl", "shaders/fragment.glsl");

    std::vector<float> vertices = {
        0.5f,  0.5f, 0.0f, 
        0.5f, 0.2f, 0.0f,  
        0.2f, 0.2f, 0.0f,  
        0.2f,  0.5f, 0.0f  
    };
    std::vector<unsigned int> indices = {  
        0, 1, 3,  
        1, 2, 3   
    };

    std::vector<float> vertices_two;
    for(size_t i = 0; i < vertices.size(); i++){
        vertices_two.push_back(vertices[i] * -1.0);
    }

    libopengl::OpenGLObject3D* square = new libopengl::OpenGLObject3D(vertexFragmentShader, vertices, indices, 3, GL_FLOAT, int(3 * sizeof(float)), 0); 
    libopengl::OpenGLObject3D* square_two = new libopengl::OpenGLObject3D(vertexFragmentShader, vertices_two, indices, 3, GL_FLOAT, int(3 * sizeof(float)), 0); 
    window->AddOpenGLObject3D(square);
    window->AddOpenGLObject3D(square_two);
    window->MainLoop();

    return 0;
}