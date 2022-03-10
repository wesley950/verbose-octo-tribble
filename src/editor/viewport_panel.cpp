#include "viewport_panel.hpp"

#include <imgui.h>

ViewportPanel::ViewportPanel(Editor::Context *context) : Panel("Viewport", context)
{
    m_UseMenuBar = false;
    m_ContentPadding = 0.0f;
}

void ViewportPanel::render_internal() {
    auto windowPos = ImGui::GetWindowPos();
    auto contentMin = ImGui::GetWindowContentRegionMin();
    auto contentMax = ImGui::GetWindowContentRegionMax();

    float contentWidth = (contentMax.x - contentMin.x);
    float contentHeight = (contentMax.y - contentMin.y);

    ImGui::Image((ImTextureID)(intptr_t)1, ImVec2(contentWidth, contentHeight));
}
