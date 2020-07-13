#ifndef OPENGLOBJECT3D_H
#define OPENGLOBJECT3D_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace libopengl
{
    class OpenGLObject3D
    {
    private:
        unsigned int VBO;

    public:
        OpenGLObject3D(float* data, int draw_method = GL_STATIC_DRAW);
    };
} // namespace libopengl

#endif // OPENGLOBJECT3D_H