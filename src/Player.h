#pragma once
#include "Rendering/Sprite.h"

class Player {
public:
    Player(std::shared_ptr<Texture> playerTexture);
    void update(float deltaTime);
    const Sprite* getSprite() const;

public:
    glm::vec2 pos;

private:
    Sprite m_playerSprite;
};
