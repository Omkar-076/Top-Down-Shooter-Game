#pragma once
#include<SDL.h>
#include<string>
#include<unordered_map>
class TextureManager {
	std::unordered_map<std::string, SDL_Texture*> textures;
public:
	bool load(SDL_Renderer* renderer,
		const std::string& name,
		const std::string& filepath);

	SDL_Texture* get(std::string name);
	void clear();
	
	~TextureManager();
};
