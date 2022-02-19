#include "Input.h"
#include <GLFW/glfw3.h>
#include <algorithm>

bool Input::m_keys[KEY_MAX] = {};
bool Input::m_keysPrev[KEY_MAX] = {};

bool Input::KeyDown(Key key) {
    return m_keys[static_cast<int>(key)];
}

bool Input::KeyPressed(Key key) {
    return m_keys[static_cast<int>(key)] && !m_keysPrev[static_cast<int>(key)];
}

void Input::inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key >= 0 && key < KEY_MAX) {
        m_keys[key] = action == GLFW_PRESS;
    }
}

void Input::update() {
    std::copy(std::begin(m_keys), std::end(m_keys), std::begin(m_keysPrev));
}
