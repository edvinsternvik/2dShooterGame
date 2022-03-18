#include "AnimatedSprite.h"
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"
#include "Rendering/SpriteData.h"
#include "TextureLoader.h"

AnimatedSprite::AnimatedSprite(const char* spritesheetfilepath, unsigned int spritesX, unsigned int spritesY, std::vector<AnimationData> animationData)
    : AnimatedSprite(loadTextureFromFile(spritesheetfilepath), spritesX, spritesY, animationData) {
}

AnimatedSprite::AnimatedSprite(std::shared_ptr<Texture> spritesheetTexture, unsigned int spritesX, unsigned int spritesY, std::vector<AnimationData> animationData) 
    : Sprite(spritesheetTexture), m_spritesheet(spritesheetTexture, spritesX, spritesY), m_animationData(animationData),
      m_animationState(0), m_animationFrame(0), m_animationFrameTimer(0) {

    m_animationFrameTimer = getAnimationStateFrameTime();
}

bool AnimatedSprite::setAnimationState(unsigned int animationStateID) {
    if(animationStateID >= m_animationData.size() || animationStateID == m_animationState) return false;
    m_animationState = animationStateID;
    m_animationFrame = m_animationFrame % getAnimationStateFrames();
    m_animationFrameTimer = getAnimationStateFrameTime();
    return true;
}

unsigned int AnimatedSprite::getAnimationState() const {
    return m_animationState;
}

void AnimatedSprite::updateAnimationFrame(float deltaTime) {
    if(m_animationState >= m_animationData.size() || m_animationData[m_animationState].frameTimes.size() == 0) return;

    m_animationFrameTimer -= deltaTime;
    if(m_animationFrameTimer <= 0.0 ) {
        m_animationFrame = (m_animationFrame + 1) % getAnimationStateFrames();

        m_animationFrameTimer = getAnimationStateFrameTime();
    }
}

void AnimatedSprite::render(glm::vec2 pos, float scale, float angle, float depthOffset, Shader* shader) const {
    glm::vec2 textureOffset = m_spritesheet.getOffset(getAnimationStateSpritesheetID() + m_animationFrame);
    glm::vec2 textureScale = m_spritesheet.getSpriteScale();
    Sprite::render(pos, scale * textureScale.x, angle, depthOffset, textureOffset, textureScale, shader);
}

void AnimatedSprite::render(glm::vec2 pos, float scale, Shader* shader) const {
    render(pos, scale, 0.0, 0.0, shader);
}

unsigned int AnimatedSprite::getAnimationStateSpritesheetID() const {
    if(m_animationState >= m_animationData.size()) return 0;
    return m_animationData[m_animationState].x + m_animationData[m_animationState].y * m_spritesheet.getNumberOfSprites().x;
}

unsigned int AnimatedSprite::getAnimationStateFrames() const {
    if(m_animationState >= m_animationData.size()) return 0;
    return std::max(static_cast<unsigned int>(m_animationData[m_animationState].frameTimes.size()), static_cast<unsigned int>(1));
    
}

float AnimatedSprite::getAnimationStateFrameTime() const {
    if(m_animationState >= m_animationData.size() || m_animationFrame >= m_animationData[m_animationState].frameTimes.size()) return 0;
    return m_animationData[m_animationState].frameTimes[m_animationFrame];
}
