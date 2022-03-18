#include "Sprite.h"
#include "Shader.h"
#include "SpriteData.h"
#include "../TextureLoader.h"
#include <memory>
#include <GL/glew.h>

#define VIEWPORT_WIDTH 320
#define VIEWPORT_HEIGHT 180

static std::unique_ptr<SpriteData> spriteData;

Sprite::Sprite(std::shared_ptr<Texture> spriteTexture)
    : m_spriteTexture(spriteTexture) {
    if(spriteData.get() == nullptr) spriteData = std::make_unique<SpriteData>();
}

Sprite::Sprite(const char* spriteFilepath)
    : Sprite(loadTextureFromFile(spriteFilepath)) {
}

void Sprite::render(glm::vec2 pos, float scale, float angle, float depthOffset, glm::vec2 textureOffset, glm::vec2 textureScale, Shader* shader) const {
    shader->useShader();
    spriteData->vao.bind();

    glm::vec2 spriteScale(
        scale * m_spriteTexture->getWidth() / static_cast<float>(VIEWPORT_WIDTH),
        scale * m_spriteTexture->getHeight() / static_cast<float>(VIEWPORT_HEIGHT)
    );

    glm::vec2 positionScale(16 / static_cast<float>(VIEWPORT_WIDTH), 16 / static_cast<float>(VIEWPORT_HEIGHT));
    pos *= positionScale;
    float depth = pos.y;
    if(angle == 0) {
        glm::mat3 transformMatrix(
            spriteScale.x, 0.0,           0.0,
            0.0f,          spriteScale.y, 0.0,
            pos.x,         pos.y,         depth
        );

        shader->setUniformMat3("u_transformMatrix", transformMatrix);
    }
    else {
        glm::mat3 transformMatrix(
            spriteScale.x *  std::cos(angle), spriteScale.x * std::sin(angle), 0.0,
            spriteScale.x * -std::sin(angle), spriteScale.y * std::cos(angle), 0.0,
            pos.x,                            pos.y,                           depth
        );
        shader->setUniformMat3("u_transformMatrix", transformMatrix);
    }

    shader->setUniform2f("u_textureOffset", textureOffset.x, textureOffset.y);
    shader->setUniform2f("u_textureScale", textureScale.x, textureScale.y);
    shader->setUniform1f("u_depthOffset", depthOffset);

    m_spriteTexture->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    spriteData->vao.unbind();
}

void Sprite::render(glm::vec2 pos, float scale, float angle, float depthOffset, Shader* shader) const {
    render(pos, scale, angle, depthOffset, glm::vec2(0.0), glm::vec2(1.0), shader);
}

void Sprite::render(glm::vec2 pos, float scale, Shader* shader) const {
    render(pos, scale, 0.0, 0.0, glm::vec2(0.0), glm::vec2(1.0), shader);
}
