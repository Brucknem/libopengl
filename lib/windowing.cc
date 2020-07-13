#include "windowing.h"
#include <exception>
#include <iostream>

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

    /**
     * @brief Exception thrown when GLFW cannot create a window.
     */
    class WindowCreationException : public std::exception
    {
    public:
        /**
             * @brief The exception message.
             * 
             * @return const char* 
             */
        virtual const char *what() const throw()
        {
            return "Failed to create GLFW window";
        }
    };

    /**
     * @brief Exception thrown when the GLAD loader cannot be initialized.
     */
    class GLADLoaderInitializationException : public std::exception
    {
        /**
         * @brief The exception message.
         * 
         * @return const char* 
         */
        virtual const char *what() const throw()
        {
            return "Failed to initialize GLAD";
        }
    };

    BaseWindow::BaseWindow(int context_minor, int context_major, int width, int height, const char *title, bool forward_compat)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context_minor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context_major);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        if (forward_compat)
        {
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        }

        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (window == NULL)
        {
            glfwTerminate();
            throw WindowCreationException();
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwTerminate();
            throw GLADLoaderInitializationException();
        }

        glViewport(0, 0, width, height);

        SetFramebufferSizeCallback(framebuffer_size_callback);
    }

    BaseWindow::~BaseWindow(){
        glfwTerminate();
    }

    void BaseWindow::SetFramebufferSizeCallback(GLFWframebuffersizefun callback){
        glfwSetFramebufferSizeCallback(window, callback);
    }

    void BaseWindow::ProcessInput(){
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void BaseWindow::MainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            ProcessInput();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }
} // namespace libopengl