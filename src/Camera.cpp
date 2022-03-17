#include "Camera.h"

void Camera::setCameraPos(glm::vec2 cameraPos) {
    m_cameraPos = cameraPos;
}

glm::vec2 Camera::getCameraPos() const {
    glm::vec2 pos = m_cameraPos;
    pos.x += cameraShakeIntensity * glm::sin(m_timer);
    pos.y += cameraShakeIntensity * glm::sin(m_timer + 100.0);
    return pos;
}

void Camera::update(float deltaTime) {
    m_timer += deltaTime;
    cameraShakeIntensity = std::max(0.0f, cameraShakeIntensity - deltaTime);
}
