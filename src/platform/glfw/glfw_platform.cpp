#include "glfw_platform.hpp"

GLFWPlatform::GLFWPlatform(Application* application) : m_Application(application) {

}

GLFWPlatform::~GLFWPlatform() {
    if (m_Application) {
        delete m_Application;
        m_Application = nullptr;
    }
}

int GLFWPlatform::run() {
    init_glfw();
    glewInit();
    m_Application->init();
    m_Running = true;

    while (m_Running) {
        glfwPollEvents();
        m_Application->update();
        m_Application->render();
        glfwSwapBuffers(m_Window);

        if (glfwWindowShouldClose(m_Window))
            quit();
    }

    shutdown_glfw();
    return m_ExitCode;
}

void GLFWPlatform::init_glfw() {
    glfwInit();
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_Window = glfwCreateWindow(1280, 720, "", nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);
}

void GLFWPlatform::shutdown_glfw() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }

    glfwTerminate();
}

Platform* create_platform() {
    return new GLFWPlatform(create_application());
}
