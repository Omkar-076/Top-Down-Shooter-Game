#include"AudioManager.h"
#include<iostream>

bool AudioManager::loadSound(const std::string& name, const std::string& filepath){
	Mix_Chunk* temp = Mix_LoadWAV(filepath.c_str());
	if (temp == nullptr) {
		std::cout << "Couldnt Load Sound: " << Mix_GetError() << std::endl;
		return false;
	}
	soundEffects[name] = temp;
	return true;
}
bool AudioManager::loadMusic(const std::string& name, const std::string& filepath) {
	Mix_Music* temp = Mix_LoadMUS(filepath.c_str());
	if (temp == nullptr) {
		std::cout << "Couldnt Load Music: " << Mix_GetError() << std::endl;
		return false;
	}
	musicTracks[name] = temp;
	return true;
}
void AudioManager::playSound(const std::string& name) {
	auto required = soundEffects.find(name);
	if (required != soundEffects.end()) {
		Mix_PlayChannel(-1, required->second, 0);
	}
	else {
		std::cout << "Sound " << required->first << " was not found." << std::endl;
	}
}
void AudioManager::playMusic(const std::string& name) {
	auto required = musicTracks.find(name);
	if(required != musicTracks.end()){
		Mix_PlayMusic(required->second, -1);
	}
	else {
		std::cout << "Music " <<required->first <<" was not found." << std::endl;
	}
}
void AudioManager::stopMusic(){
	Mix_HaltMusic();
}
void AudioManager::clear() {
	for (const auto& pair : soundEffects) {
		Mix_FreeChunk(pair.second);
	}
	for(const auto& pair : musicTracks){
		Mix_FreeMusic(pair.second);
	}
	soundEffects.clear();
	musicTracks.clear();
}
void AudioManager::setMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}
void AudioManager::setSoundVolume(int volume) {
	Mix_Volume(-1, volume);
}

AudioManager::~AudioManager() {
	clear();
}