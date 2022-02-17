#pragma once
#include <memory>
#include <glm/glm.hpp>

class Shader;
class Spritesheet;

template <unsigned int width, unsigned int height>
class Tileset {
public:
    Tileset(std::shared_ptr<Spritesheet> spritesheet);

    void render(Shader* shader);
    bool setSprite(unsigned int x, unsigned int y, unsigned int spriteID);

private:
    std::shared_ptr<Spritesheet> m_spritesheet;
    glm::vec2 m_spriteOffsets[width * height];
    glm::ivec2 m_nSprites;
};

