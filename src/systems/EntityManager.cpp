#include"EntityManager.h"
#include"../entities/Bullet.h"
void EntityManager::createBullet(ShootRequest shootRequest) {
	Bullet bullet(shootRequest);
}