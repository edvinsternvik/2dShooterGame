#include "CollisionManager.h"
#include <iostream>

std::shared_ptr<BoxCollider> CollisionManager::registerCollider(std::shared_ptr<BoxCollider> collider) {
    m_colliders.push_back(collider);
    return collider;
}

void CollisionManager::checkCollisions() {
    for(std::size_t i = 0; i < m_colliders.size(); ++i) {
        if(m_colliders[i].use_count() < 2) { // Remove collider if it is not referenced anywhere else
            m_colliders[i] = m_colliders[m_colliders.size() - 1];
            m_colliders.pop_back();
        }

        if(!m_colliders[i]->isStatic) {
            for(std::size_t j = 0; j < m_colliders.size(); ++j) {
                if(m_colliders[j]->isStatic || j > i) {
                    if(m_colliders[i]->isColliding(m_colliders[j].get())) {
                        if(m_colliders[i]->m_collisionCallback) m_colliders[i]->m_collisionCallback(m_colliders[j].get());
                        if(m_colliders[j]->m_collisionCallback) m_colliders[j]->m_collisionCallback(m_colliders[i].get());
                    }
                }
            }
        }
    }
}
