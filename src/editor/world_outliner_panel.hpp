#pragma once

#include "panel.hpp"

#include <entt/entt.hpp>

class WorldOutlinerPanel : public Panel {
public:
    WorldOutlinerPanel(Editor::Context* context);
    ~WorldOutlinerPanel();

public:
    void render_internal() override;

    void show_hierarchy_node(entt::handle node);
};