#include "BoxCollider.h"
#include "CollisionManager.h"

BoxCollider::BoxCollider() : BoxCollider(true) {
}

BoxCollider::BoxCollider(bool isStatic) 
    : isStatic(isStatic), collisionLayer(0) {
}

void BoxCollider::updatePos(const glm::vec2& pos, const glm::vec2& size) {
    bottomLeft = pos;
    topRight = pos + size;
}

bool BoxCollider::isColliding(BoxCollider* other) const {
    return bottomLeft.x < other->topRight.x && topRight.x > other->bottomLeft.x
        && bottomLeft.y < other->topRight.y && topRight.y > other->bottomLeft.y;
}

void BoxCollider::setCollisionCallback(std::function<void(BoxCollider* other)>& callbackFn) {
    m_collisionCallback = callbackFn;
}
