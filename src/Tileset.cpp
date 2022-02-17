#include "Tileset.h"
#include "Spritesheet.h"
#include "Rendering/SpriteData.h"
#include "Rendering/Shader.h"
#include <GL/glew.h>
#include <memory>

static std::unique_ptr<SpriteData> spriteData;

template <unsigned int width, unsigned int height>
Tileset<width, height>::Tileset(std::shared_ptr<Spritesheet> spritesheet)
    : m_spritesheet(spritesheet) {
    if(spriteData.get() == nullptr) spriteData = std::make_unique<SpriteData>();
    m_nSprites = (glm::ivec2(width, height) + m_spritesheet->getSpriteSize() - glm::ivec2(1, 1)) / m_spritesheet->getSpriteSize();

    for(int i = 0; i < width * height; ++i) {
        m_spriteOffsets[i] = glm::vec2(0.0, 0.0);
    }
}

template <unsigned int width, unsigned int height>
void Tileset<width, height>::render(Shader* shader) {
    shader->useShader();
    shader->setUniform2fv("u_spriteOffsets", width*height, &(m_spriteOffsets[0][0]));

    glm::vec2 tileScale = m_spritesheet->getSpriteSize();
    tileScale.x /= static_cast<float>(width);
    tileScale.y /= static_cast<float>(height);
    shader->setUniform2f("u_tileScale", tileScale.x, tileScale.y);

    shader->setUniform2i("u_nSprites", m_nSprites.x, m_nSprites.y);

    glm::vec2 spriteScale = m_spritesheet->getSpriteScale();
    shader->setUniform2f("u_spriteScale", spriteScale.x, spriteScale.y);

    spriteData->vao.bind();
    m_spritesheet->getTexture()->bind();
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, m_nSprites.x * m_nSprites.y);
}

template <unsigned int width, unsigned int height>
bool Tileset<width, height>::setSprite(unsigned int x, unsigned int y, unsigned int spriteID) {
    unsigned int index = x * y;
    if(index >= width * height) return false;

    m_spriteOffsets[index] = m_spritesheet->getOffset(spriteID);
    return true;
}

template class Tileset<320, 180>;
