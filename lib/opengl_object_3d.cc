#include "opengl_object_3d.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "iostream"

namespace libopengl
{
    OpenGLObject3D::OpenGLObject3D(libopengl::Shader* shader, std::vector<float> vertices, std::vector<unsigned int> indices, int sizes, int types, int strides, int offsets, int drawMethod) : OpenGLObject3D(shader, std::vector<std::vector<float> >{vertices}, std::vector<std::vector<unsigned int> >{indices}, std::vector<int>{sizes}, std::vector<int>{types}, std::vector<int>{strides}, std::vector<int>{offsets}, drawMethod){}

    OpenGLObject3D::OpenGLObject3D(libopengl::Shader* shader, std::vector<std::vector<float> > vertices, std::vector<std::vector<unsigned int> > indices, std::vector<int> sizes, std::vector<int> types, std::vector<int> strides, std::vector<int> offsets, int drawMethod) : shader(shader)
    {
        int num_buffers = vertices.size();
        num_indices = std::vector<int>(num_buffers);
        for(size_t i = 0; i < indices.size(); i++){
            num_indices[i] = indices[i].size();
        }

        VBOs = std::vector<GLuint>(num_buffers);
        VAOs = std::vector<GLuint>(num_buffers);
        EBOs = std::vector<GLuint>(num_buffers);

        glGenVertexArrays(num_buffers, VAOs.data());
        glGenBuffers(num_buffers, VBOs.data());
        glGenBuffers(num_buffers, EBOs.data());

        for(int i = 0; i < num_buffers; i++){
            glBindVertexArray(VAOs[i]);

            glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
            glBufferData(GL_ARRAY_BUFFER, vertices[i].size() * sizeof(float), vertices[i].data(), drawMethod);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices[i].size() * sizeof(unsigned int), indices[i].data(), drawMethod);

            glVertexAttribPointer(i, sizes[i], types[i], GL_FALSE, strides[i], reinterpret_cast<void*>(offsets[i]));
            glEnableVertexAttribArray(i);

            glBindBuffer(GL_ARRAY_BUFFER, 0); 
            glBindVertexArray(0); 
        }
    }

    OpenGLObject3D::~OpenGLObject3D(){
        glDeleteVertexArrays(num_buffers, VAOs.data());
        glDeleteBuffers(num_buffers, VBOs.data());
        glDeleteBuffers(num_buffers, EBOs.data());
    }

    void OpenGLObject3D::Render()
    {
        shader->Activate();

        for(size_t i = 0; i < VAOs.size(); i++){
            glBindVertexArray(VAOs[i]);
            glDrawElements(GL_TRIANGLES, num_indices[i], GL_UNSIGNED_INT, 0);
        }
    }
} // namespace libopengl
