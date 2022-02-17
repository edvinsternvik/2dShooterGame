#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "Rendering/Texture.h"

class Spritesheet {
public:
    Spritesheet(std::shared_ptr<Texture> tilesetTexture, unsigned int spritesX, unsigned int spritesY);

    glm::vec2 getOffset(unsigned int spriteID) const;
    Texture* getTexture() const;
    glm::ivec2 getSpriteSize() const;
    glm::vec2 getSpriteScale() const;
    glm::ivec2 getNumberOfSprites() const;

private:
    unsigned int m_spritesX, m_spritesY;
    std::shared_ptr<Texture> m_tilesetTexture;
    std::vector<glm::vec2> m_spriteOffsets;
};
