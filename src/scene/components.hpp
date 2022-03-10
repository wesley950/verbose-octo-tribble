#pragma once

#include <string>
#include <vector>

#include <entt/entt.hpp>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "core/uuid.hpp"

// Core Components

struct Tag
{
    std::string tag;
    UUID uuid;
};

struct Transform
{
    glm::vec2 position{0.0f, 0.0f};
    glm::vec2 scale{1.0f, 1.0f};
    float angle = 0.0f;

    glm::mat4 get_transformation()
    {
        glm::mat4 rotationMatrix = glm::toMat4(glm::quat(glm::vec3(0.0f, 0.0f, glm::radians(angle))));
        return glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) * rotationMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
    }
};

struct Hierarchy
{
    entt::entity parent;
    std::vector<entt::entity> children;
};

// Graphics related components

struct Sprite
{
    glm::vec2 size{1.0f, 1.0f};
    glm::vec2 center{0.5f, 0.5f};
    glm::vec4 color{1.0f, 1.0f, 1.0f, 1.0f};
};
