#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
#include <memory>

class Shader;

class Sprite {
public:
    Sprite(std::shared_ptr<Texture> spriteTexture);
    Sprite(const char* spriteFilepath);

    void render(glm::vec2 pos, float scale, float angle, float depthOffset, glm::vec2 textureOffset, glm::vec2 textureScale, Shader* shader) const;
    virtual void render(glm::vec2 pos, float scale, float angle, float depthOffset, Shader* shader) const;
    virtual void render(glm::vec2 pos, float scale, Shader* shader) const;

private:
    std::shared_ptr<Texture> m_spriteTexture;
};
