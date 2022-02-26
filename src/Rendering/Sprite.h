#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
#include <memory>

class Shader;

class Sprite {
public:
    Sprite(std::shared_ptr<Texture> spriteTexture);
    Sprite(const char* spriteFilepath);

    void render(glm::vec2 pos, float scale, float angle, Shader* shader) const;
    void render(glm::vec2 pos, float scale, Shader* shader) const;

private:
    std::shared_ptr<Texture> m_spriteTexture;
};
