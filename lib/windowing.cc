#include "windowing.h"
#include <exception>
#include <iostream>
#include <stdexcept>

namespace libopengl
{
    /**
     * @brief Callback for the glfw window resize event.
     * 
     * @param window The window pointer.
     * @param width The new width of the window. 
     * @param height The new height of the window.
     */
    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    };

    BaseWindow::BaseWindow(int context_minor, int context_major, int width, int height, const char *title)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context_minor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context_major);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (window == NULL)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwTerminate();
            throw std::runtime_error("Failed to initialize GLAD");
        }

        glViewport(0, 0, width, height);

        SetFramebufferSizeCallback(framebuffer_size_callback);
    }

    BaseWindow::~BaseWindow()
    {
        glfwTerminate();
    }

    void BaseWindow::SetFramebufferSizeCallback(GLFWframebuffersizefun callback)
    {
        glfwSetFramebufferSizeCallback(window, callback);
    }

    void BaseWindow::ProcessInput()
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void BaseWindow::MainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            ProcessInput();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (const auto &openGLObject3D : openGLObjects3D)
            {
                openGLObject3D->Render();
            }

            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }

    void BaseWindow::AddOpenGLObject3D(libopengl::OpenGLObject3D *openGL3DObject)
    {
        openGLObjects3D.push_back(openGL3DObject);
    }

    MockWindow::MockWindow(int context_minor, int context_major, int width, int height, const char *title) : BaseWindow(context_minor, context_major, width, height, title) {}

    void MockWindow::MainLoop()
    {
        for (int i = 0; i < 100; i++)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }

} // namespace libopengl