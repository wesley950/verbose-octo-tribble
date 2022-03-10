#pragma once

#include "editor.hpp"

#include <string>

#include <entt/entt.hpp>

#include <imgui.h>

class Panel {
public:
    Panel(const std::string& title, Editor::Context* context);
    virtual ~Panel();

    void render();
    bool& is_open() { return m_Open; }
    const std::string& get_title() const { return m_Title; }

protected:
    virtual void render_internal() = 0;

protected:
    std::string m_Title;
    Editor::Context* m_Context = nullptr;
    bool m_Open = true;
    bool m_UseMenuBar = true;
    float m_ContentPadding = 8.0f;
};
