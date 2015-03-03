#pragma once

#include "Entity.h"
#include "EnemyAbility.h"
#include "Animation.h"
#include <map>
#include <vector>

class EnemyAbility;

class Enemy : public Entity
{
public:
	char * name;
	int healthPoints;
	int maxHealthPoints;
	int magicPoints;
	int maxMagicPoints;

	int imageWidth;
	int imageHeight;

	bool turnDone;

	std::string currentAnimation;
	std::map<std::string, Animation*> animations;

	std::vector<EnemyAbility*> abilities;

	Enemy::Enemy();
	void Enemy::AddAnimation(std::string n, Animation *a);
};