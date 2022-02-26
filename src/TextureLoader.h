#pragma once
#include <memory>
#include "Rendering/Texture.h"

std::shared_ptr<Texture> loadTextureFromFile(const char* texturePath);
