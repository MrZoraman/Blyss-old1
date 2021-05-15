#ifndef BLYSS_GLFWCONTEXT_H_
#define BLYSS_GLFWCONTEXT_H_

namespace Blyss
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