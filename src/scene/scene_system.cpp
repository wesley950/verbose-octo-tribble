#include "scene_system.hpp"
#include "components.hpp"

entt::registry* SceneSystem::s_Context = nullptr;

void SceneSystem::init(entt::registry* context) {
    s_Context = context;
}

entt::handle SceneSystem::create_basic() {
    entt::handle basic { *s_Context, s_Context->create() };

    basic.emplace<Tag>().tag = "Basic Entity";
    basic.emplace<Transform>();
    basic.emplace<Hierarchy>();

    return basic;
}

entt::handle SceneSystem::create_child(entt::handle parent) {
    entt::handle child = create_basic();

    auto& parentHierarchy = parent.get<Hierarchy>();
    parentHierarchy.children.push_back(child.entity());

    auto& childHierarchy = child.get<Hierarchy>();
    childHierarchy.parent = parent.entity();

    return child;
}
