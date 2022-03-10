#pragma once

#include "panel.hpp"

#include <entt/entt.hpp>

class InspectorPanel : public Panel {
public:
    InspectorPanel(Editor::Context* context);

public:
    void render_internal() override;

private:
    void render_menu_bar();
};
