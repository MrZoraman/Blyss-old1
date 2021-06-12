#ifndef BLYSS_GLFWCONTEXT_H
#define BLYSS_GLFWCONTEXT_H

namespace blyss
{
    /**
     * @brief GLFW context. This class only exists so that GLFW's state init and destroy functions
     * can be called using RAII.
    */
    class GLFWContext final
    {
    public:
        GLFWContext();
        ~GLFWContext();

        GLFWContext(const GLFWContext&) = delete;
        GLFWContext(GLFWContext&&) = delete;
        GLFWContext& operator=(const GLFWContext&) = delete;
        GLFWContext& operator=(GLFWContext&&) = delete;
    };
}

#endif
