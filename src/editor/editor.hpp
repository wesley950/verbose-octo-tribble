#pragma once

#include "core/application.hpp"

#include <vector>

#include <entt/entt.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class Panel;

class Editor : public Application {
public:
    struct Context {
        entt::registry m_Registry;
        entt::handle m_SceneRoot;
        entt::handle m_SelectedEntity;
    };

    Editor() = default;
    virtual ~Editor() override;

    void init() override;
    void update() override;
    void render() override;

private:
    void reset_context();

    void init_imgui();
    void imgui_new_frame();
    void imgui_render();
    void shutdown_imgui();

private:
    Context m_Context;

    bool m_ShowDemoWindow = false;
    std::vector<Panel*> m_Panels;
};
