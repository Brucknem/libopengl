#ifndef OPENGLOBJECT3D_H
#define OPENGLOBJECT3D_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "lib/shader.h"
#include <vector>
namespace libopengl
{
    /**
     * @brief Base class for all OpenGL 3D objects.
     */
    class OpenGLObject3D
    {
    protected:
        /**
         * @brief The OpenGL buffers.
         */
        std::vector<GLuint> VBOs, VAOs, EBOs;

        /**
         * @brief The number of triangle indices.
         */
        std::vector<int> num_indices;

        /**
         * @brief The total number of buffers. 
         */
        int num_buffers = 0;

        /**
         * @brief The shader to render the buffers. 
         */
        libopengl::Shader* shader;

    public:
        /**
         * @brief Construct a new Open GL 3D Object with a single vertex and index buffer.
         * 
         * @param shader The shader to render the buffers. 
         * @param vertices The vertices to render.
         * @param indices The indices in which order to render the vertices.
         * @param sizes The number of values of a single vertex component.
         * @param types The type of the values per single vertex component.
         * @param strides The offset between two consecutive vertices in the vertices.
         * @param offsets The offsets of the respective buffer from the start of the vertices. 
         * @param drawMethod The draw method.
         */
        OpenGLObject3D(libopengl::Shader* shader, std::vector<float> vertices, std::vector<unsigned int> indices, int sizes, int types, int strides, int offsets, int drawMethod = GL_STATIC_DRAW);

        /**
         * @brief Construct a new Open GL 3D Object with multiple vertex and index buffer.
         * 
         * @param shader The shader to render the buffers. 
         * @param vertices The vertices to render.
         * @param indices The indices in which order to render the vertices.
         * @param sizes The number of values of a single vertex component.
         * @param types The type of the values per single vertex component.
         * @param strides The offset between two consecutive vertices in the vertices.
         * @param offsets The offsets of the respective buffer from the start of the vertices. 
         * @param drawMethod The draw method.
         */
        OpenGLObject3D(libopengl::Shader* shader, std::vector<std::vector<float> > vertices, std::vector<std::vector<unsigned int> > indices, std::vector<int> sizes, std::vector<int> types, std::vector<int> strides, std::vector<int> offsets, int drawMethod = GL_STATIC_DRAW);

        /**
         * @brief Destroy the Open GL 3D Object
         */
        ~OpenGLObject3D();

        /**
         * @brief Render itself.
         */
        void Render();
    };
} // namespace libopengl

#endif // OPENGLOBJECT3D_H