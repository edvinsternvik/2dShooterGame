#include "Spritesheet.h"
#include "Rendering/SpriteData.h"
#include "Rendering/Shader.h"
#include <GL/glew.h>
#include <memory>

Spritesheet::Spritesheet(std::shared_ptr<Texture> tilesetTexture, unsigned int spritesX, unsigned int spritesY)
    : m_spritesX(spritesX), m_spritesY(spritesY), m_tilesetTexture(tilesetTexture) {

    for(int i = 0; i < m_spritesX * m_spritesY; ++i) {
        glm::vec2 offset;
        offset.x = (i % m_spritesX) / static_cast<float>(m_spritesX);
        offset.y = (m_spritesY - 1 - (i / m_spritesX)) / static_cast<float>(m_spritesY);
        m_spriteOffsets.push_back(offset);
    }
}

glm::vec2 Spritesheet::getOffset(unsigned int spriteID) const {
    if(spriteID < m_spriteOffsets.size()) return m_spriteOffsets[spriteID];
    return glm::vec2(0.0, 0.0);
}

Texture* Spritesheet::getTexture() const {
    return m_tilesetTexture.get();
}

glm::ivec2 Spritesheet::getSpriteSize() const {
    return glm::ivec2(m_tilesetTexture->getWidth() / m_spritesX, m_tilesetTexture->getHeight() / m_spritesY);
}

glm::vec2 Spritesheet::getSpriteScale() const {
    return glm::vec2(1.0 / m_spritesX, 1.0 / m_spritesY);
}

glm::ivec2 Spritesheet::getNumberOfSprites() const {
    return glm::ivec2(m_spritesX, m_spritesY);
}
