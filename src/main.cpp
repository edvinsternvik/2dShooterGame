#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <iostream>
#include <chrono>

#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Rendering/Sprite.h"
#include "Spritesheet.h"
#include "Tileset.h"
#include "Input.h"
#include "Player.h"
#include "TextureLoader.h"

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

    Shader tilemapShader(loadFile("assets/shaders/tilemapVertexShader.glsl").c_str(), loadFile("assets/shaders/tilemapFragmentShader.glsl").c_str());
    Shader spriteShader(loadFile("assets/shaders/spriteVertexShader.glsl").c_str(), loadFile("assets/shaders/spriteFragmentShader.glsl").c_str());

    std::shared_ptr<Texture> spritesheetTexture = loadTextureFromFile("assets/sprites/spritesheet.png");
    std::shared_ptr<Spritesheet> spritesheet = std::make_shared<Spritesheet>(spritesheetTexture, 8, 8);
    Tileset<320, 180> tileset(spritesheet);
    for(int x = 0; x < 320; x++) {
        for(int y = 0; y < 180; ++y) {
            tileset.setSprite(x, y, 2);
        }
    }

    std::shared_ptr<Sprite> playerSprite = std::make_shared<Sprite>("assets/sprites/player.png");
    Player player;
    player.setSprite(playerSprite);

    std::chrono::high_resolution_clock::time_point frameTimePoint = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point prevFrameTimePoint;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        prevFrameTimePoint = frameTimePoint;
        frameTimePoint = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(frameTimePoint - prevFrameTimePoint).count() * 0.000000001;

        player.update(deltaTime);

        tileset.render(&tilemapShader);

        player.render(&spriteShader);

        Input::update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
