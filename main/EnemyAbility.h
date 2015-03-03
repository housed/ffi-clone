#pragma once
#include "SDL_Mixer.h"
#include "EnemyAbility.h"
#include "PartyMember.h"
#include "Enemy.h"
#include <iostream>
#include <string>
#include <vector>

class Enemy;
class PartyMember;

class EnemyAbility
{
public:
	int currentState;
	long checkTime;

	int currentX;
	int currentY;

	PartyMember * selectedParty;

	std::vector<PartyMember*> partyList;

	virtual bool EnemyAbility::Action(Enemy * e);
	virtual bool EnemyAbility::ReadyAbility(std::vector<PartyMember*> p);
};

class EnemyAttack : public EnemyAbility
{
public :
	Mix_Chunk* sHit;
	int move_dir;

	EnemyAttack::EnemyAttack();
	bool EnemyAttack::Action(Enemy * e);
	bool EnemyAttack::ReadyAbility(std::vector<PartyMember*> p);
};