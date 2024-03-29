#pragma once
#include "Entity.h"
#include "BoxCollider.h"
#include "Game.h"
#include <memory>

class Wall : public Entity {
public:
    Wall(glm::vec2 pos, glm::vec2 size)
        : boxCollider(std::make_shared<BoxCollider>(true)) {

        setPos(pos);
        boxCollider->updatePos(pos, size);
        Game::collisionManager.registerCollider(boxCollider);
    }

    std::shared_ptr<BoxCollider> boxCollider;
};

