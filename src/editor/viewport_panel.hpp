#pragma once

#include "panel.hpp"

class ViewportPanel : public Panel {
public:
    ViewportPanel(Editor::Context* context);

public:
    void render_internal() override;
};

