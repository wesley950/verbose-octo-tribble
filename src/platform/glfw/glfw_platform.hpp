#include "core/platform.hpp"
#include "core/application.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

class GLFWPlatform : public Platform {
public:
    GLFWPlatform(Application* application = nullptr);
    virtual ~GLFWPlatform() override;

    int run() override;

private:
    void init_glfw();
    void shutdown_glfw();

private:
    GLFWwindow* m_Window = nullptr;
    Application* m_Application = nullptr;
};
