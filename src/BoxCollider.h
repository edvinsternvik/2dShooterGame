#pragma once
#include <glm/glm.hpp>
#include <functional>

class BoxCollider {
public:
    BoxCollider();
    BoxCollider(bool isStatic);
    void updatePos(const glm::vec2& pos, const glm::vec2& size);
    bool isColliding(BoxCollider* other) const;
    void setCollisionCallback(std::function<void(BoxCollider* other)> callbackFn);

public:
    bool isStatic;
    unsigned int collisionLayer;
    glm::vec2 bottomLeft;
    glm::vec2 topRight;

private:
    std::function<void(BoxCollider* other)> m_collisionCallback;

    friend class CollisionManager;
};
