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
#include "EntityManager.h"
#include "CollisionManager.h"
#include "Wall.h"
#include "Bullet.h"

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

    EntityManager entityManager;
    CollisionManager collisionManager;

    std::shared_ptr<Sprite> playerSprite = std::make_shared<Sprite>("assets/sprites/player.png");
    entityID playerID = entityManager.create<Player>();
    Player* player = entityManager.getEntity<Player>(playerID);
    player->setSprite(playerSprite);
    collisionManager.registerCollider(player->boxCollider);

    Wall* wallBottom = entityManager.getEntity<Wall>(entityManager.create<Wall>(glm::vec2(0, -1), glm::vec2(20, 1)));
    collisionManager.registerCollider(wallBottom->boxCollider);
    Wall* wallLeft = entityManager.getEntity<Wall>(entityManager.create<Wall>(glm::vec2(-1, 0), glm::vec2(1, 12)));
    collisionManager.registerCollider(wallLeft->boxCollider);
    Wall* wallTop = entityManager.getEntity<Wall>(entityManager.create<Wall>(glm::vec2(0, 11), glm::vec2(20, 1)));
    collisionManager.registerCollider(wallTop->boxCollider);
    Wall* wallRight = entityManager.getEntity<Wall>(entityManager.create<Wall>(glm::vec2(20, 0), glm::vec2(1, 12)));
    collisionManager.registerCollider(wallRight->boxCollider);

    std::shared_ptr<Sprite> bulletSprite = std::make_shared<Sprite>("assets/sprites/bullet.png");
    Bullet* bullet = entityManager.getEntity<Bullet>(entityManager.create<Bullet>());
    bullet->pos = glm::vec2(5, 5);
    bullet->setSprite(bulletSprite);
    collisionManager.registerCollider(bullet->boxCollider);

    std::chrono::high_resolution_clock::time_point frameTimePoint = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point prevFrameTimePoint;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        prevFrameTimePoint = frameTimePoint;
        frameTimePoint = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(frameTimePoint - prevFrameTimePoint).count() * 0.000000001;

        entityManager.updateEntities(deltaTime);
        collisionManager.checkCollisions();

        tileset.render(&tilemapShader);

        entityManager.renderEntities(&spriteShader);

        Input::update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
