#include"TextureManager.h"
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
bool TextureManager::load(SDL_Renderer* renderer, const std::string& name, const std::string& filepath) {
    SDL_Surface* surface = IMG_Load(filepath.c_str());
    if (surface == nullptr)
    {
        std::cout << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) {
        return false;
    }
    textures[name] = texture;
    return true;
}

SDL_Texture* TextureManager::get(const std::string& name) {
    auto required =  textures.find(name);
    if (required != textures.end()) {
        return required->second;
    }
    return nullptr;
}

void TextureManager::clear() {
    for (const auto& pair : textures) {
        SDL_Texture* texture = pair.second;
        SDL_DestroyTexture(texture);
    }
    textures.clear();
}

TextureManager::~TextureManager() {
    clear();
}