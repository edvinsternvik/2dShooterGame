#pragma once
#include "Entity.h"

class Player : public Entity {
public:
    virtual void update(float deltaTime) override;
};
