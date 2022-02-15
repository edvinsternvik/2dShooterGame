#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>

#include "Rendering/Shader.h"
#include "Rendering/Sprite.h"

std::string loadFile(const char* filename) {
    std::ifstream file(filename);
    if(!file.is_open()) return "";

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "2dShooterGame", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK) {
        return -1;
    }

    Shader shader(loadFile("assets/shaders/vertexShader.glsl").c_str(), loadFile("assets/shaders/fragmentShader.glsl").c_str());
    shader.useShader();

    float angle = 0.0;
    glm::vec2 pos(0.0, 0.0);
    Sprite sprite;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        sprite.render(pos, angle, &shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
