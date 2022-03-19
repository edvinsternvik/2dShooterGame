#pragma once
#include "BoxCollider.h"
#include <memory>

class CollisionManager {
public:
    CollisionManager();
    std::shared_ptr<BoxCollider> registerCollider(std::shared_ptr<BoxCollider> collider);
    void checkCollisions();

    std::size_t getLayerCount() const;
    void setLayerCount(unsigned int nLayers);
    bool setLayerCollision(unsigned int layer1, unsigned int layer2, bool collides);
    bool checkLayerCollision(unsigned int layer1, unsigned int layer2) const;

private:
    std::vector<std::weak_ptr<BoxCollider>> m_colliders;
    std::vector<std::vector<bool>> m_layers;
};
