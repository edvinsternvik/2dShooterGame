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
#include "Game.h"
#include "Enemy.h"
#include "Shadow.h"

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
    glfwSetCursorPosCallback(window, Input::cursorCallback);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader tilemapShader(loadFile("assets/shaders/tilemapVertexShader.glsl").c_str(), loadFile("assets/shaders/tilemapFragmentShader.glsl").c_str());
    Shader spriteShader(loadFile("assets/shaders/spriteVertexShader.glsl").c_str(), loadFile("assets/shaders/spriteFragmentShader.glsl").c_str());

    std::shared_ptr<Texture> spritesheetTexture = loadTextureFromFile("assets/sprites/spritesheet.png");
    std::shared_ptr<Spritesheet> spritesheet = std::make_shared<Spritesheet>(spritesheetTexture, 8, 8);
    Tileset<320, 180> tileset(spritesheet);
    for(int x = 0; x < 320; x++) {
        for(int y = 0; y < 180; ++y) {
            tileset.setSprite(x, y, 3 + (std::rand() % 5));
        }
    }

    // 0: Enviroment
    // 1: Player
    // 2: Enemies
    // 3: Player bullets
    // 4: Enemy bullets
    Game::collisionManager.setLayerCount(8);
    Game::collisionManager.setLayerCollision(0, 3, true);
    Game::collisionManager.setLayerCollision(0, 4, true);
    Game::collisionManager.setLayerCollision(1, 4, true);
    Game::collisionManager.setLayerCollision(2, 3, true);

    entityID playerID = Game::entityManager.create<Player>();
    Game::entityManager.create<Shadow>(playerID);

    Wall* wallBottom = Game::entityManager.getEntity<Wall>(Game::entityManager.create<Wall>(glm::vec2(0, -1), glm::vec2(20, 1)));
    Wall* wallLeft = Game::entityManager.getEntity<Wall>(Game::entityManager.create<Wall>(glm::vec2(-1, 0), glm::vec2(1, 12)));
    Wall* wallTop = Game::entityManager.getEntity<Wall>(Game::entityManager.create<Wall>(glm::vec2(0, 11), glm::vec2(20, 1)));
    Wall* wallRight = Game::entityManager.getEntity<Wall>(Game::entityManager.create<Wall>(glm::vec2(20, 0), glm::vec2(1, 12)));

    std::shared_ptr<Sprite> enemySprite = std::make_shared<Sprite>("assets/sprites/player.png");
    Enemy* enemy1 = Game::entityManager.getEntity<Enemy>(Game::entityManager.create<Enemy>());
    enemy1->setPos(glm::vec2(5, 5));
    enemy1->setTarget(playerID);
    Enemy* enemy2 = Game::entityManager.getEntity<Enemy>(Game::entityManager.create<Enemy>());
    enemy2->setPos(glm::vec2(10, 2));
    enemy2->setTarget(playerID);
    Enemy* enemy3 = Game::entityManager.getEntity<Enemy>(Game::entityManager.create<Enemy>());
    enemy3->setPos(glm::vec2(16, 4));
    enemy3->setTarget(playerID);

    Game::camera.setCameraPos(glm::vec2(0.0));

    std::chrono::high_resolution_clock::time_point frameTimePoint = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point prevFrameTimePoint;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        prevFrameTimePoint = frameTimePoint;
        frameTimePoint = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(frameTimePoint - prevFrameTimePoint).count() * 0.000000001;

        Game::entityManager.updateEntities(deltaTime);
        Game::collisionManager.checkCollisions();
        Game::camera.update(deltaTime);

        glm::vec2 cameraPos = Game::camera.getCameraPos();
        tilemapShader.useShader();
        tilemapShader.setUniform2f("u_cameraPos", cameraPos.x, cameraPos.y);
        tileset.render(&tilemapShader);

        glClear(GL_DEPTH_BUFFER_BIT);
        spriteShader.useShader();
        spriteShader.setUniform2f("u_cameraPos", cameraPos.x, cameraPos.y);
        Game::entityManager.renderEntities(&spriteShader);

        Input::update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
