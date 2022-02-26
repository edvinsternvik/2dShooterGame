#pragma once
#include "Entity.h"
#include "BoxCollider.h"
#include <memory>

class Wall : public Entity {
public:
    Wall(glm::vec2 pos, glm::vec2 size)
        : boxCollider(std::make_shared<BoxCollider>(true)) {

        this->pos = pos;
        boxCollider->updatePos(pos, size);
    }

    std::shared_ptr<BoxCollider> boxCollider;
};

