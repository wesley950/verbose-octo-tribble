#include "world_outliner_panel.hpp"
#include "editor.hpp"

#include "scene/components.hpp"
#include "scene/scene_system.hpp"

WorldOutlinerPanel::WorldOutlinerPanel(Editor::Context *context) : Panel("World Outliner", context)
{
}

WorldOutlinerPanel::~WorldOutlinerPanel()
{
}

void WorldOutlinerPanel::render_internal()
{
    // Menu bar
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Entity"))
        {
            if (ImGui::MenuItem("Create Basic"))
            {
                if (m_Context->m_Registry.valid(m_Context->m_SelectedEntity.entity()))
                    SceneSystem::create_child(m_Context->m_SelectedEntity);
                else
                    SceneSystem::create_child(m_Context->m_SceneRoot);
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    // Hierarchy tree
    show_hierarchy_node(m_Context->m_SceneRoot);
}

void WorldOutlinerPanel::show_hierarchy_node(entt::handle node)
{
    auto& tagComponent = node.get<Tag>();
    auto& hierarchyComponent = node.get<Hierarchy>();

    bool hasChildren = hierarchyComponent.children.size() > 0;
    bool isSelected = (node == m_Context->m_SelectedEntity);
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | 
                                ImGuiTreeNodeFlags_OpenOnDoubleClick |
                                ImGuiTreeNodeFlags_OpenOnArrow;

    if (!hasChildren)
        flags |= ImGuiTreeNodeFlags_Leaf;

    if (isSelected)
        flags |= ImGuiTreeNodeFlags_Selected;

    bool open = ImGui::TreeNodeEx((const void*)(intptr_t)tagComponent.uuid.get(), flags, "%s", tagComponent.tag.c_str());

    if (ImGui::IsItemClicked()) {
        m_Context->m_SelectedEntity = node;
    }

    if (open) {
        if (hasChildren) {
            for (entt::entity childEntity : hierarchyComponent.children) {
                show_hierarchy_node({ m_Context->m_Registry, childEntity });
            }
        }

        ImGui::TreePop();
    }
}
