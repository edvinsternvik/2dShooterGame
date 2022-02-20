#include "Player.h"
#include "Input.h"
#include <iostream>

Player::Player(std::shared_ptr<Texture> playerTexture)
    : m_playerSprite(playerTexture), pos(0.0, 0.0) {
    
}

void Player::update(float deltaTime) {
    float speed = 8.0;
    if(Input::KeyDown(Key::KEY_W)) pos.y += speed * deltaTime;
    if(Input::KeyDown(Key::KEY_S)) pos.y -= speed * deltaTime;
    if(Input::KeyDown(Key::KEY_A)) pos.x -= speed * deltaTime;
    if(Input::KeyDown(Key::KEY_D)) pos.x += speed * deltaTime;

    if(pos.x < 0) pos.x = 0;
    if(pos.x > 19) pos.x = 19;
    if(pos.y < 0) pos.y = 0;
    if(pos.y > 10.25) pos.y = 10.25;
}

const Sprite* Player::getSprite() const {
    return &m_playerSprite;
}
