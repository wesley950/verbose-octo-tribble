#include "panel.hpp"

Panel::Panel(const std::string &title, Editor::Context *context) : m_Title(title), m_Context(context) {}

Panel::~Panel()
{
    m_Context = nullptr;
}

void Panel::render()
{
    if (!m_Open)
        return;

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;

    if (m_UseMenuBar)
        windowFlags |= ImGuiWindowFlags_MenuBar;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(m_ContentPadding, m_ContentPadding));

    if (ImGui::Begin(m_Title.c_str(), &m_Open, windowFlags))
    {
        render_internal();
    }
    ImGui::End();

    ImGui::PopStyleVar();
}
