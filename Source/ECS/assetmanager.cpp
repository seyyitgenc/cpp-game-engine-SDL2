#include "ECS/assetmanager.h"

#include <iostream>

AssetManager *AssetManager::s_instance;
AssetManager::AssetManager() {
    if (TTF_Init() != 0) std::cerr << TTF_GetError() << std::endl;
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0)
        std::cerr << TTF_GetError() << std::endl;
}

Texture *AssetManager::getTexture(std::string id) {
    // if texture is exist then return
    return (textures.count(id) > 0) ? textures[id] : nullptr;
}

void AssetManager::loadTexture(std::string id, std::string path) {
    if (textures.count(id) <=
        0)  // if same texture is exist don't create new texture
    {
        Texture *texture = new Texture();
        if (texture->loadFromFile(path)) {
            textures.emplace(id, texture);
            std::cout << "Texture :[" << path << "] loaded" << std::endl;
        } else {
            std::cerr << IMG_GetError() << std::endl;
        }
    }
}
void AssetManager::loadFont(std::string id, std::string path, int fontSize) {
    TTF_Font *newFont = TTF_OpenFont(path.c_str(), fontSize);
    if (newFont != nullptr) {
        fonts.emplace(
            id,
            newFont);  // this section ensures that font saved only once
        std::cout << "Font :[" << path << "] loaded" << std::endl;
    } else
        std::cerr << TTF_GetError() << std::endl;
}
TTF_Font *AssetManager::getFont(std::string id) {
    if (fonts.count(id) > 0) return fonts[id];
    return nullptr;
}

// this cleans everything related to Textures and Fonts
void AssetManager::clean() {
    for (auto it = textures.begin(); it != textures.end(); it++) {
        it->second->free();  // free SDL_Texture
        delete it->second;   // delete Texture object
    }
    textures.clear();
    std::cout << "Textures Cleared !" << std::endl;

    for (auto it = fonts.begin(); it != fonts.end(); it++) {
        TTF_CloseFont(it->second);
    }
    fonts.clear();
    std::cout << "Fonts Cleared !" << std::endl;
}