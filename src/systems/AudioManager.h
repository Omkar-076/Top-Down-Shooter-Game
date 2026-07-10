#pragma once
#include<SDL.h>
#include<string>
#include<SDL_mixer.h>
#include<unordered_map>
class AudioManager {
	std::unordered_map<std::string, Mix_Chunk*> soundEffects;
	std::unordered_map<std::string, Mix_Music*> musicTracks;
public:
	bool loadSound(const std::string& name, const std::string& filepath);
	bool loadMusic(const std::string& name, const std::string& filepath);
	void playSound(const std::string& name);
	void playMusic(const std::string& name);
	void stopMusic();
	void setMusicVolume(int volume);
	void setSoundVolume(int volume);
	void clear();
	~AudioManager();
};