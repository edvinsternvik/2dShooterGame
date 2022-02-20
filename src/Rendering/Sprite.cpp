#include "Sprite.h"
#include "Shader.h"
#include "SpriteData.h"
#include <memory>
#include <GL/glew.h>

#define VIEWPORT_WIDTH 320
#define VIEWPORT_HEIGHT 180

static std::unique_ptr<SpriteData> spriteData;

Sprite::Sprite(std::shared_ptr<Texture> spriteTexture)
    : m_spriteTexture(spriteTexture) {
    if(spriteData.get() == nullptr) spriteData = std::make_unique<SpriteData>();
}

void Sprite::render(glm::vec2 pos, float scale, float angle, Shader* shader) const {
    spriteData->vao.bind();

    glm::vec2 spriteScale(
        scale * m_spriteTexture->getWidth() / static_cast<float>(VIEWPORT_WIDTH),
        scale * m_spriteTexture->getHeight() / static_cast<float>(VIEWPORT_HEIGHT)
    );

    if(angle == 0) {
        glm::mat3 transformMatrix(
            spriteScale.x, 0.0,           pos.x,
            0.0,           spriteScale.y, pos.y,
            0.0,           0.0,           1.0
        );
        shader->setUniformMat3("u_transformMatrix", transformMatrix);
    }
    else {
        glm::mat3 transformMatrix(
            spriteScale.x * std::cos(angle), spriteScale.x * -std::sin(angle), pos.x,
            spriteScale.y * std::sin(angle), spriteScale.y *  std::cos(angle), pos.y,
            0.0,                              0.0,                             1.0
        );
        shader->setUniformMat3("u_transformMatrix", transformMatrix);
    }

    m_spriteTexture->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    spriteData->vao.unbind();
}

void Sprite::render(glm::vec2 pos, float scale, Shader* shader) const {
    render(pos, scale, 0.0, shader);
}
