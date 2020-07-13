#include "opengl_object_3d.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace libopengl
{
    OpenGLObject3D::OpenGLObject3D(float* data, int draw_method)
    {
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, draw_method);
    }
} // namespace libopengl
