#include "Player.h"
#include<iostream>
#include<SDL.h>
Player::Player() {
    cPx = cPy = 0;
    MdirX = MdirY = 0;
    pw = ph = 80;
    px = 400 - pw / 2;
    py = 300 - ph / 2;
    dX = dY = 0;
    speed = 150.0f;
    length = 0.0f;
    wantsToShoot = false;
    shootRequest = { 0,0,0,0 };
    offsetX = offsetY = 0;
    rect = { 0,0,0,0 };
    isAlive = true;
    textures = {};
    rotation = 0;
    direction = RIGHT;
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
        shootRequest.spawnX = cPx + offsetX;
        shootRequest.spawnY = cPy + offsetY;
        shootRequest.dirX = MdirX;
        shootRequest.dirY = MdirY;  
    }
    rotation = -atan2(MdirY, MdirX) * 180/M_PI +90;
    int temp;
    if (rotation < 0) {
        rotation += 360;
    }
    temp = (rotation + 22.5) / 45;
    temp = (temp + 6) % 8;
    std::cout << temp << std::endl;
    rect = { (int)px, (int)py, pw, ph };

    switch (temp) {
    case 0:
        direction = RIGHT;
        offsetX = 26;
        offsetY = -7;
        break;
    case 1:
        direction = UP_RIGHT;
        offsetX = 7;
        offsetY = -35;
        break;
    case 2:
        direction = UP;
        offsetX = -7;
        offsetY = -35;
        break;
    case 3:
        direction = UP_LEFT;
        offsetX = -28;
        offsetY = -33;
        break;
    case 4:
        direction = LEFT;
        offsetX = -35;
        offsetY = -6;
        break;
    case 5:
        direction = DOWN_LEFT;
        offsetX = -32;
        offsetY = 15;
        break;
    case 6:
        direction = DOWN;
        offsetX = -6;
        offsetY = 20;
        break;
    case 7:
        direction = DOWN_RIGHT;
        offsetX = 12;
        offsetY = 10;
        break;
    default:
        direction = RIGHT;
        offsetX = 26;
        offsetY = -7;
        break;
    }
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
    SDL_RenderCopy(renderer, textures[direction], nullptr, &rect);
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

void Player::restart() {
    px = 400 - pw/2;
    py = 300 - ph/2;
    cPx = cPy = 0;
    MdirX = MdirY = 0;
    pw = ph = 45;
    dX = dY = 0;
    speed = 150.0f;
    length = 0.0f;
    wantsToShoot = false;
    shootRequest = { 0,0,0,0 };
    offsetX = offsetY =  0;
    rect = { 0,0,0,0 };
    isAlive = true;
    rotation = 0;
}

void Player::setTextures(const std::array<SDL_Texture*,8>& textures) {
    this->textures = textures;
}