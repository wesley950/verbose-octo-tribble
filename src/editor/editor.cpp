#include "editor.hpp"

#include "world_outliner_panel.hpp"
#include "inspector_panel.hpp"
#include "viewport_panel.hpp"

#include "core/entry_point.hpp"

#include "scene/components.hpp"
#include "scene/scene_system.hpp"

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>

Editor::~Editor()
{
    for (Panel* panel : m_Panels) {
        delete panel;
    }

    shutdown_imgui();
}

void Editor::init()
{
    SceneSystem::init(&m_Context.m_Registry);
    reset_context();
    init_imgui();

    m_Panels.push_back(new WorldOutlinerPanel(&m_Context));
    m_Panels.push_back(new InspectorPanel(&m_Context));
    m_Panels.push_back(new ViewportPanel(&m_Context));
}

void Editor::update()
{
}

void Editor::render()
{
    imgui_new_frame();
    for (Panel* panel : m_Panels) {
        panel->render();
    }
    imgui_render();
}

void Editor::reset_context() {
    m_Context.m_Registry = entt::registry{};
    m_Context.m_SceneRoot = SceneSystem::create_basic();
    m_Context.m_SceneRoot.get<Tag>().tag = "Scene Root";
}

void Editor::init_imgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    GLFWwindow *window = glfwGetCurrentContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void Editor::imgui_new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("View")) {
            ImGui::MenuItem("ImGui Demo Window", nullptr, &m_ShowDemoWindow);

            ImGui::Separator();
            for (Panel* panel : m_Panels) {
                ImGui::MenuItem(panel->get_title().c_str(), nullptr, &panel->is_open());
            }

            ImGui::EndMenu();
        }


        ImGui::EndMainMenuBar();
    }
}

void Editor::imgui_render()
{
    if (m_ShowDemoWindow)
        ImGui::ShowDemoWindow(&m_ShowDemoWindow);

    // ImGui rendering
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *mainWindow = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(mainWindow);
        }
    }
}

void Editor::shutdown_imgui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

Application *create_application()
{
    return new Editor();
}