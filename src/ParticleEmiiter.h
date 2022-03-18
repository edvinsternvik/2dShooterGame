#pragma once
#include "Entity.h"
#include <vector>

struct Particle {
    Particle(float lifetime, float gravity, glm::vec2 vel, glm::vec2 offset, float height)
        : lifetime(lifetime), gravity(gravity), vel(vel), offset(offset), height(height) {}
    float lifetime;
    float gravity;
    glm::vec2 vel;
    glm::vec2 offset;
    float height;
};

class ParticleEmitter : public Entity {
public:
    ParticleEmitter(glm::uvec2 nParticlesRange, glm::vec2 lifetimeRange, glm::vec2 gravityRange, glm::vec2 angleRange, glm::vec2 speedRange, glm::vec2 startOffsetRange, glm::vec2 heightRange);
    virtual void update(float deltaTime) override;
    virtual void render(Shader* shader) override;

private:
    std::vector<Particle> m_particles;
    static std::shared_ptr<Sprite> particleSprite;
};
