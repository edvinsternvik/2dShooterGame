#include "Shadow.h"
#include "Game.h"

std::shared_ptr<Sprite> Shadow::shadowSprite;

Shadow::Shadow(entityID target) : m_target(target) {
    if(shadowSprite.get() == nullptr) shadowSprite = std::make_shared<Sprite>("assets/sprites/shadow.png");
    setSprite(shadowSprite);
}

void Shadow::update(float deltaTime) {
    Entity* target = Game::entityManager.getEntity(m_target);

    if(target != nullptr) {
        setPos(target->getPos() + glm::vec2(0.0, -0.25));
        
    }
}
