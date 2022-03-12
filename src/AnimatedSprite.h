#pragma once
#include "Rendering/Sprite.h"
#include "Spritesheet.h"
#include <vector>

class Shader;

struct AnimationData {
    AnimationData(unsigned int x, unsigned int y, std::vector<float> frameTimes)
        : x(x), y(y), frameTimes(frameTimes) {}
    const unsigned int x;
    const unsigned int y;
    const std::vector<float> frameTimes;
};

class AnimatedSprite : public Sprite {
public:
    AnimatedSprite(const char* spritesheetfilepath, unsigned int spritesX, unsigned int spritesY, std::vector<AnimationData> animationData);
    AnimatedSprite(std::shared_ptr<Texture> spritesheetTexture, unsigned int spritesX, unsigned int spritesY, std::vector<AnimationData> animationData);

    bool setAnimationState(unsigned int animationStateID);
    unsigned int getAnimationState() const;
    void updateAnimationFrame(float deltaTime);

    virtual void render(glm::vec2 pos, float scale, float angle, Shader* shader) const override;
    virtual void render(glm::vec2 pos, float scale, Shader* shader) const override;

private:
    unsigned int getAnimationStateSpritesheetID() const;
    unsigned int getAnimationStateFrames() const;
    float getAnimationStateFrameTime() const;
    
private:
    Spritesheet m_spritesheet;
    std::vector<AnimationData> m_animationData;
    unsigned int m_animationState;
    unsigned int m_animationFrame;
    float m_animationFrameTimer;
};
