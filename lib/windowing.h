#ifndef WINDOWING_H
#define WINDOWING_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "opengl_object_3d.h"

namespace libopengl
{
    /**
     * @brief Base class for my OpenGL/GLFW windows.
     * 
     */
    class BaseWindow
    {
    private:
        /**
         * @brief A list of OpenGL 3D objects.
         */
        std::vector<libopengl::OpenGLObject3D*> openGLObjects3D;

    protected:
        /**
         * @brief Called in the main loop to process mouse and keyboard events. 
         */
        virtual void ProcessInput();

    public:
        /**
         * @brief The actual window object 
         */
        GLFWwindow *window;

        /**
         * @brief Constructor for OpenGL/GLFW Windows. 
         * Sets the necessary window hints, makes the window the current context,
         * loads GLAD and sets the FramebufferSize callback.  
         * 
         * @param context_minor The OpenGL minor context version
         * @param context_major The OpenGL major context version
         * @param width The initial window width
         * @param height The initial window height
         * @param title The window title 
         * @return GLFWwindow* 
         */
        BaseWindow(int context_minor, int context_major, int width, int height, const char *title);

        /**
         * @brief Destroy the Base Window object. 
         */
        virtual ~BaseWindow();

        /**
         * @brief Set the Framebuffer Size Callback of the OpenGL/GLFW window.
         * 
         * @param callback The callback function.
         */
        void SetFramebufferSizeCallback(GLFWframebuffersizefun callback);

        /**
         * @brief The window main loop. 
         */
        void virtual MainLoop();

        /**
         * @brief Adds a OpenGL 3D object to the list of rendered objects.
         * 
         * @param openGL3DObject The OpenGL 3D object.
         */
        void AddOpenGLObject3D(libopengl::OpenGLObject3D *openGL3DObject);
    };

    /**
 * @brief A Mock window with a 100 frame long main loop.
 * 
 */
    class MockWindow : public BaseWindow
    {
    public:
    
        /**
         * @brief Construct a new Mock Window object.
         * 
         * @param context_minor The OpenGL minor context version
         * @param context_major The OpenGL major context version
         * @param width The initial window width
         * @param height The initial window height
         * @param title The window title 
         * @return GLFWwindow* 
         */
        MockWindow(int context_minor, int context_major, int width, int height, const char *title);

        /**
         * @brief The window main loop. Terminates after 100 frames.
         */
        void MainLoop() override;

        /**
         * @brief Destroy the Mock Window object
         */
        virtual ~MockWindow(){}
    };
} // namespace libopengl

#endif // WINDOWING_H