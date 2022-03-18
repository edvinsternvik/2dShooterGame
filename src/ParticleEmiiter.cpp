#include "ParticleEmiiter.h"

std::shared_ptr<Sprite> ParticleEmitter::particleSprite;

ParticleEmitter::ParticleEmitter(glm::uvec2 nParticlesRange, glm::vec2 lifetimeRange, glm::vec2 gravityRange, glm::vec2 angleRange, glm::vec2 speedRange, glm::vec2 startOffsetRange, glm::vec2 heightRange) {
    if(nParticlesRange.y < nParticlesRange.x) nParticlesRange.y = nParticlesRange.x;
    unsigned int nParticles = nParticlesRange.x + (std::rand() % (nParticlesRange.y + 1 - nParticlesRange.x));
    for(int i = 0; i < nParticles; ++i) {
        auto getFloatFromRange = [](glm::vec2 range) {
            return range.x + (range.y - range.x) * (std::rand() / static_cast<float>(RAND_MAX));
        };

        float lifetime = getFloatFromRange(lifetimeRange);
        float gravity = getFloatFromRange(gravityRange);
        float angle = getFloatFromRange(angleRange);
        float speed = getFloatFromRange(speedRange);
        glm::vec2 vel = glm::vec2(std::cos(angle), std::sin(angle)) * speed;
        float startOffsetLen = getFloatFromRange(startOffsetRange);
        float startOffsetAngle = getFloatFromRange(glm::vec2(0.0f, glm::radians(360.0f)));
        glm::vec2 startOffset = glm::vec2(std::cos(startOffsetAngle), std::sin(startOffsetAngle)) * startOffsetLen;
        float height = getFloatFromRange(heightRange);
        m_particles.push_back(Particle(lifetime, gravity, vel, startOffset, height));
    }

    if(particleSprite.get() == nullptr) particleSprite = std::make_shared<Sprite>("assets/sprites/particle.png");
    setSprite(particleSprite);
}

void ParticleEmitter::update(float deltaTime) {
    bool alive = false;
    for(int i = 0; i < m_particles.size(); ++i) {
        Particle& particle = m_particles[i];
        if(particle.lifetime <= 0) continue;
        alive = true;

        particle.vel += glm::vec2(0.0, -1.0) * particle.gravity * deltaTime;
        particle.offset += particle.vel * deltaTime;
        if(particle.offset.y < -particle.height) {
            particle.offset.y = -particle.height;
            particle.vel = glm::vec2(0.0);
        }
        particle.lifetime -= deltaTime;

    }

    if(!alive) markDestroyed();
}

void ParticleEmitter::render(Shader* shader) {
    glm::vec2 pos = getPos();
    for(int i = 0; i < m_particles.size(); ++i) {
        Particle& particle = m_particles[i];
        if(particle.lifetime <= 0) continue;
        setPos(pos + particle.offset);
        depthOffset = (particle.height + particle.offset.y) / 8.0;
        Entity::render(shader);
    }
    setPos(pos);
}
