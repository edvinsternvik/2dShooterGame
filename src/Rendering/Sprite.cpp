#include "Sprite.h"
#include "VertexBuffer.h"
#include "VertexArrayObject.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <memory>
#include <GL/glew.h>

float vertexData[] {
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0
};

unsigned int indexData[] {
    0, 1, 2, 2, 3, 0
};

class SpriteData {
public:
    SpriteData() : vao(), vbo({VertexAttribute(2, VertexAttributeType::FLOAT, false)}), ibo() {
        vao.bind();

        vbo.setData(vertexData, sizeof(vertexData), BufferDataUsage::STATIC_DRAW);
        vbo.bind();

        ibo.setData(indexData, sizeof(indexData), BufferDataUsage::STATIC_DRAW);
        ibo.bind();

        vao.unbind();
    }

public:
    VertexArrayObject vao;
    VertexBuffer vbo;
    IndexBuffer ibo;
};

static std::unique_ptr<SpriteData> spriteData;

Sprite::Sprite() {
    if(spriteData.get() == nullptr) spriteData = std::make_unique<SpriteData>();
}

void Sprite::render(glm::vec2 pos, float angle, Shader* shader) {
    spriteData->vao.bind();

    if(angle == 0) {
        glm::mat3 transformMatrix(
            1.0, 0.0, pos.x,
            0.0, 1.0, pos.y,
            0.0, 0.0, 1.0
        );
        shader->setUniformMat3("u_transformMatrix", transformMatrix);
    }
    else {
        glm::mat3 transformMatrix(
            std::cos(angle), -std::sin(angle), pos.x,
            std::sin(angle),  std::cos(angle), pos.y,
            0.0,             0.0,              1.0
        );
        shader->setUniformMat3("u_transformMatrix", transformMatrix);
    }

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    spriteData->vao.unbind();
}

void Sprite::render(glm::vec2 pos, Shader* shader) {
    render(pos, 0.0, shader);
}
