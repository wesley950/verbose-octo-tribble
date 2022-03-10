#include "inspector_panel.hpp"
#include "editor.hpp"

#include "scene/components.hpp"
#include "scene/scene_system.hpp"

#include <cstring>

InspectorPanel::InspectorPanel(Editor::Context *context) : Panel("Inspector", context)
{
}

template <typename T, typename UIFunc>
static void draw_component_inspector_panel(const char *szTitle, T &component, UIFunc uiFunc)
{
    if (ImGui::CollapsingHeader(szTitle, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick))
    {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 0.8f), "%s Component", szTitle);
        uiFunc(component);
    }
}

void InspectorPanel::render_internal()
{
    render_menu_bar();

    static const int NAME_BUFFER_SIZE = 256;
    static char nameBuffer[NAME_BUFFER_SIZE] = {0};

    if (!m_Context->m_Registry.valid(m_Context->m_SelectedEntity))
        return;

    entt::handle entity = m_Context->m_SelectedEntity;
    auto &tagComponent = entity.get<Tag>();

    std::snprintf(nameBuffer, NAME_BUFFER_SIZE, "%s", tagComponent.tag.c_str());

    if (ImGui::InputText("##EntityTagInput", nameBuffer, NAME_BUFFER_SIZE - 1, ImGuiInputTextFlags_EnterReturnsTrue))
        tagComponent.tag = std::string(nameBuffer);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 0.5f), "%lx", tagComponent.uuid.get());
    ImGui::Separator();

    // Component handling
    {
        bool hasSprite = entity.all_of<Sprite>();

        if (hasSprite)
        {
            auto &sprite = entity.get<Sprite>();
            draw_component_inspector_panel("Sprite", sprite, [](Sprite &sprite)
                                           {
                glm::vec2& size = sprite.size;
                glm::vec2& center = sprite.center;
                glm::vec4& color = sprite.color;

                ImGui::DragFloat2("Size", (float*)&size, 0.1f, -999.0f, 999.0f, "%.02f");
                ImGui::DragFloat2("Center", (float*)&center, 0.1f, -999.0f, 999.0f, "%.02f");
                ImGui::ColorEdit4("Color", (float*)&color); });
        }
    }
}

template <typename T>
static void handle_component_toggle(const char *szName, entt::handle entity)
{
    bool selected = entity.all_of<T>();

    if (ImGui::MenuItem(szName, nullptr, selected))
    {
        if (selected)
            entity.remove<T>();
        else
            entity.emplace<T>();
    }
}

void InspectorPanel::render_menu_bar()
{
    if (!m_Context->m_Registry.valid(m_Context->m_SelectedEntity))
        return;

    entt::handle entity = m_Context->m_SelectedEntity;

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Entity"))
        {
            if (ImGui::BeginMenu("Components"))
            {
                handle_component_toggle<Sprite>("Sprite", entity);
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}
