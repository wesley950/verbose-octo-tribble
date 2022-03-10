#pragma once

#include <entt/entt.hpp>

class SceneSystem {
public:
    static void init(entt::registry* context);

    static entt::handle create_basic();
    static entt::handle create_child(entt::handle parent);

public:
    static entt::registry* s_Context;
};
