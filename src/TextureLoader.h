#pragma once
#include <memory>
#include "Rendering/Texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

std::shared_ptr<Texture> loadTextureFromFile(const char* texturePath) {
    stbi_set_flip_vertically_on_load(true);
    int spriteX, spriteY, channels;
    unsigned char* tilesetTextureData = stbi_load(texturePath, &spriteX, &spriteY, &channels, 4);
    if(tilesetTextureData == nullptr) std::cout << "Error loading " << texturePath << std::endl;
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->bind();
    texture->textureImage2D(TextureFormat::RGBA, spriteX, spriteY, tilesetTextureData);
    texture->setFilterMode(TextureFilterMode::NEAREST);
    return texture;
}


