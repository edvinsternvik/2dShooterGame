#pragma once
#include <glm/glm.hpp>

class Camera {
public:
    void setCameraPos(glm::vec2 cameraPos);
    glm::vec2 getCameraPos() const;
    void update(float deltaTime);
    
public:
    float cameraShakeIntensity;

private:
    glm::vec2 m_cameraPos;
    float m_timer;
};
