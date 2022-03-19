#include "CollisionManager.h"

CollisionManager::CollisionManager() {
    setLayerCount(1);
    m_layers[0][0] = true;
}

std::shared_ptr<BoxCollider> CollisionManager::registerCollider(std::shared_ptr<BoxCollider> collider) {
    m_colliders.push_back(collider);
    return collider;
}

void CollisionManager::checkCollisions() {
    for(std::size_t i = 0; i < m_colliders.size();) {
        if(m_colliders[i].expired()) { // Remove collider if it is not referenced anywhere else
            m_colliders[i] = m_colliders[m_colliders.size() - 1];
            m_colliders.pop_back();
            continue;
        }

        std::shared_ptr<BoxCollider> collider = m_colliders[i].lock();
        if(!collider->isStatic) {
            for(std::size_t j = 0; j < m_colliders.size(); ++j) {
                std::shared_ptr<BoxCollider> other = m_colliders[j].lock();
                if(other.get() != nullptr && (other->isStatic || j > i)) {
                    unsigned int layer1 = collider->collisionLayer;
                    unsigned int layer2 = other->collisionLayer;
                    if(checkLayerCollision(layer1, layer2) && collider->isColliding(other.get())) {
                        if(collider->m_collisionCallback) collider->m_collisionCallback(other.get());
                        if(other->m_collisionCallback) other->m_collisionCallback(collider.get());
                    }
                }
            }
        }
        ++i;
    }
}

std::size_t CollisionManager::getLayerCount() const {
    return m_layers.size();
}

void CollisionManager::setLayerCount(unsigned int nLayers) {
    if(nLayers < m_layers.size()) {
        m_layers.resize(nLayers);
    }
    while(nLayers > m_layers.size()) {
        std::size_t layerCount = getLayerCount();
        m_layers.push_back(std::vector<bool>(layerCount + 1, false));
    }
}

bool CollisionManager::setLayerCollision(unsigned int layer1, unsigned int layer2, bool collides) {
    if(layer1 < layer2) std::swap(layer1, layer2);
    if(layer1 >= getLayerCount()) return false;
    m_layers[layer1][layer2] = collides;
    return true;
}

bool CollisionManager::checkLayerCollision(unsigned int layer1, unsigned int layer2) const {
    if(layer1 < layer2) std::swap(layer1, layer2);
    if(layer1 >= getLayerCount()) return false;
    return m_layers[layer1][layer2];
}
