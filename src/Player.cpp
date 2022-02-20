#include "Player.h"
#include "Input.h"

Player::Player(std::shared_ptr<Texture> playerTexture)
    : m_playerSprite(playerTexture), pos(0.0, 0.0) {
    
}

void Player::update(float deltaTime) {
    float speed = 1.0;
    if(Input::KeyDown(Key::KEY_W)) pos.y += speed * deltaTime;
    if(Input::KeyDown(Key::KEY_S)) pos.y -= speed * deltaTime;
    if(Input::KeyDown(Key::KEY_A)) pos.x -= speed * deltaTime;
    if(Input::KeyDown(Key::KEY_D)) pos.x += speed * deltaTime;
}

const Sprite* Player::getSprite() const {
    return &m_playerSprite;
}
