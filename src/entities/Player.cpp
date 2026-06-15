#include "Player.h"
#include<iostream>
#include<SDL.h>
Player::Player() {
    px = 350;
    py = 250;
    cPx = cPy = 0;
    MdirX = MdirY = 0;
    pw = ph = 75;
    dX = dY = 0;
    speed = 200.0f;
    length = 0.0f;
    wantsToShoot = false;
    shootRequest = { 0,0,0,0 };
    offset = 55;
    rect = { 0,0,0,0 };
    isAlive = true;
}
void Player::update(int movement, int mx, int my, bool wantsToShoot, float deltaTime) {
    this->wantsToShoot = wantsToShoot;
    //Keyboard Updates
    if (movement & 1) {
        dY += -1;
    }
    if (movement & 2) {
        dX += 1;
    }
    if (movement & 4) {
        dY += 1;
    }
    if (movement & 8) {
        dX += -1;
    }
    length = sqrt(dX * dX + dY * dY);
    if (length) {
        dX /= length;
        dY /= length;
    }
    px += dX * speed * deltaTime;
    py += dY * speed * deltaTime;
    cPx = px + pw / 2;  
    cPy = py + ph / 2;
    dX = dY = 0.0f;
    
    //Mouse Updates
    MdirX = mx - cPx;
    MdirY = my - cPy;
    length = sqrt(MdirX * MdirX + MdirY * MdirY);
    if (length >= 0.001) {
        MdirX /= length;
        MdirY /= length;
    }
    else {
        MdirX = MdirY = 0;
    }
    if (wantsToShoot) {
        //Determine bullet spawn location
        shootRequest.spawnX = cPx + offset*MdirX;
        shootRequest.spawnY = cPy + offset*MdirY;
        shootRequest.dirX = MdirX;
        shootRequest.dirY = MdirY;  
    }
    rect = { (int)px, (int)py, pw, ph };
}
bool Player::hasShootRequest() {
    if(wantsToShoot && (length >= 0.001))
        return true;
    return false;
}

ShootRequest Player::consumeShootRequest() {
    wantsToShoot = false;
    return shootRequest;
}
void Player::render(SDL_Renderer* renderer) {
   SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
   SDL_RenderFillRect(renderer, &rect);
}
float Player::getPx() {
    return cPx;
}
float Player::getPy() {
    return cPy;
}
void Player::markDead() {
    isAlive = false;
}
bool Player::isDead() {
    return !isAlive;
}