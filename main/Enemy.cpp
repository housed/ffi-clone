#include "Enemy.h"

Enemy::Enemy()
{
	imageWidth = 0;
	turnDone = false;
	currentAnimation = "Idle";
}
void Enemy::AddAnimation(std::string n, Animation *a)
{
	animations[n] = a;
}