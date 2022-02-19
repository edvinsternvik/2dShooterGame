#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Rendering/Sprite.h"
#include "Spritesheet.h"
#include "Tileset.h"
#include "Input.h"

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

    glfwWindowHint(GLFW_RESIZABLE, false);
    window = glfwCreateWindow(1280, 720, "2dShooterGame", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK) {
        return -1;
    }

    glfwSetKeyCallback(window, Input::inputCallback);

    Shader shader(loadFile("assets/shaders/vertexShader.glsl").c_str(), loadFile("assets/shaders/fragmentShader.glsl").c_str());
    shader.useShader();

    float angle = 0;
    glm::vec2 pos(0.0, 0.0);
    //Sprite sprite;

    stbi_set_flip_vertically_on_load(true);
    int spriteX, spriteY, channels;
    unsigned char* spriteData = stbi_load("assets/sprites/spritesheet.png", &spriteX, &spriteY, &channels, 4);
    if(spriteData == nullptr) std::cout << "Error loading spritesheet.png" << std::endl;
    std::shared_ptr<Texture> spriteTexture = std::make_shared<Texture>();
    spriteTexture->bind();
    spriteTexture->textureImage2D(TextureFormat::RGBA, spriteX, spriteY, spriteData);
    spriteTexture->setFilterMode(TextureFilterMode::NEAREST);

    std::shared_ptr<Spritesheet> spritesheet = std::make_shared<Spritesheet>(spriteTexture, 8, 8);
    Tileset<320, 180> tileset(spritesheet);
    for(int x = 0; x < 320; x++) {
        for(int y = 0; y < 180; ++y) {
            tileset.setSprite(x, y, 2);
        }
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        Input::update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
