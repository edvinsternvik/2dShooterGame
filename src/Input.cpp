#include "Input.h"
#include <GLFW/glfw3.h>
#include <algorithm>

std::array<bool, KEY_MAX> Input::m_keys;
std::array<bool, KEY_MAX> Input::m_keysPrev;
glm::vec2 Input::m_cursorPos = {};

bool Input::KeyDown(Key key) {
    return m_keys[static_cast<int>(key)];
}

bool Input::KeyPressed(Key key) {
    return m_keys[static_cast<int>(key)] && !m_keysPrev[static_cast<int>(key)];
}

glm::vec2 Input::GetCursorPos() {
    return m_cursorPos;
}

void Input::inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key >= 0 && key < KEY_MAX) {
        if(action == GLFW_PRESS) m_keys[key] = true;
        if(action == GLFW_RELEASE) m_keys[key] = false;
    }
}

void Input::cursorCallback(GLFWwindow* window, double xpos, double ypos) {
    glm::ivec2 windowSize;
    glfwGetFramebufferSize(window, &windowSize.x, &windowSize.y);
    m_cursorPos = glm::vec2(xpos, ypos) / glm::vec2(windowSize);
}

void Input::update() {
    m_keysPrev = m_keys;
}
