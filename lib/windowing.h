#ifndef WINDOWING_H
#define WINDOWING_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace libopengl
{
    /**
     * @brief Base class for my OpenGL/GLFW windows.
     * 
     */
    class BaseWindow {
        private: 
            /**
             * @brief The actual window object 
             */
            GLFWwindow* window;

        protected:
            /**
             * @brief Called in the main loop to process mouse and keyboard events. 
             */
            virtual void ProcessInput();

        public:
            /**
             * @brief Constructor for my OpenGL/GLFW Window. 
             * Sets the necessary window hints, makes the window the current context,
             * loads GLAD and sets the FramebufferSize callback.  
             * 
             * @param context_minor The OpenGL minor context version
             * @param context_major The OpenGL major context version
             * @param width The initial window width
             * @param height The initial window height
             * @param title The window title 
             * @param forward_compat Enable OpenGL forward compatibility
             * @return GLFWwindow* 
             */
            BaseWindow(int context_minor, int context_major, int width, int height, const char *title, bool forward_compat = false);

            /**
             * @brief Destroy the Base Window object. 
             */
            ~BaseWindow();

            /**
             * @brief Set the Framebuffer Size Callback of the OpenGL/GLFW window.
             * 
             * @param callback The callback function.
             */
            void SetFramebufferSizeCallback(GLFWframebuffersizefun callback);

            /**
             * @brief The window main loop. 
             */
            void MainLoop();
    };
} // namespace libopengl

#endif // WINDOWING_H