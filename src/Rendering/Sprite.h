#pragma once
#include <glm/glm.hpp>

class Shader;

class Sprite {
public:
    Sprite();

    void render(glm::vec2 pos, float angle, Shader* shader);
    void render(glm::vec2 pos, Shader* shader);
};
