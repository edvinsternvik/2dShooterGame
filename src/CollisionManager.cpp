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
    for(std::size_t i = 0; i < m_colliders.size(); ++i) {
        if(m_colliders[i].use_count() < 2) { // Remove collider if it is not referenced anywhere else
            m_colliders[i] = m_colliders[m_colliders.size() - 1];
            m_colliders.pop_back();
        }

        if(!m_colliders[i]->isStatic) {
            for(std::size_t j = 0; j < m_colliders.size(); ++j) {
                if(m_colliders[j]->isStatic || j > i) {
                    unsigned int layer1 = m_colliders[i]->collisionLayer;
                    unsigned int layer2 = m_colliders[j]->collisionLayer;
                    if(checkLayerCollision(layer1, layer2) && m_colliders[i]->isColliding(m_colliders[j].get())) {
                        if(m_colliders[i]->m_collisionCallback) m_colliders[i]->m_collisionCallback(m_colliders[j].get());
                        if(m_colliders[j]->m_collisionCallback) m_colliders[j]->m_collisionCallback(m_colliders[i].get());
                    }
                }
            }
        }
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
