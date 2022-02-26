#pragma once
#include "BoxCollider.h"
#include <memory>

class CollisionManager {
public:
    std::shared_ptr<BoxCollider> registerCollider(std::shared_ptr<BoxCollider> collider);
    void checkCollisions();
    
private:
    std::vector<std::shared_ptr<BoxCollider>> m_colliders;
};
