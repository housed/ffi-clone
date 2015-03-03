#pragma once

#include "Weapons.h"
#include "Entity.h"
#include "Enemy.h"
#include "Ability.h"
#include "Animation.h"
#include <vector>
#include <string>
#include <map>

class Ability;
class Weapons;
class Enemy;

class PartyMember : public Entity
{
public:
	std::string name;
	std::string weaponEquipped;
	int healthPoints;
	int maxHealthPoints;
	int magicPoints;
	int maxMagicPoints;
	bool evasive;
	bool dead;
	bool turnDone;

	std::string currentAnimation;
	std::map<std::string, Animation*> animations;

	std::vector<Weapons*> weapons;
	std::vector<Ability*> abilities;

	PartyMember::PartyMember();
	void PartyMember::AddAnimation(std::string n, Animation *a);
};