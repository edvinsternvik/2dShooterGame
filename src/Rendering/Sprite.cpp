#include "Sprite.h"
#include "Shader.h"
#include "SpriteData.h"
#include <memory>
#include <GL/glew.h>

static std::unique_ptr<SpriteData> spriteData;

Sprite::Sprite() {
    if(spriteData.get() == nullptr) spriteData = std::make_unique<SpriteData>();
}

void Sprite::render(glm::vec2 pos, float scale, float angle, Shader* shader) {
    spriteData->vao.bind();

    if(angle == 0) {
        glm::mat3 transformMatrix(
            scale, 0.0, pos.x,
            0.0, scale, pos.y,
            0.0, 0.0, scale
        );
        shader->setUniformMat3("u_transformMatrix", transformMatrix);
    }
    else {
        glm::mat3 transformMatrix(
            scale * std::cos(angle), scale * -std::sin(angle), pos.x,
            scale * std::sin(angle), scale *  std::cos(angle), pos.y,
            0.0,             0.0,              1.0
        );
        shader->setUniformMat3("u_transformMatrix", transformMatrix);
    }

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    spriteData->vao.unbind();
}

void Sprite::render(glm::vec2 pos, float scale, Shader* shader) {
    render(pos, scale, 0.0, shader);
}
