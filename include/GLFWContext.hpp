#ifndef BLYSS_GLFWCONTEXT_H
#define BLYSS_GLFWCONTEXT_H

namespace blyss
{
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