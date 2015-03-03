#pragma once
#include "PartyMember.h"
#include "Enemy.h"
#include "SDL.h"
#include <iostream>
#include <string>
#include "SDL_Mixer.h"

class PartyMember;
class Enemy;

class Ability
{
public:
	std::string name;
	int currentState;
	long checkTime;
	bool requireEnemy;

	int currentX;
	int currentY;
	int enemies;
	int partyMembers;

	PartyMember *parent;
	Enemy *selectedEnemy;
	Enemy *selectedEnemy1;
	Enemy *selectedEnemy2;
	Enemy *selectedEnemy3;
	Enemy *selectedEnemy4;
	PartyMember *selectedPartyMember;
	PartyMember *selectedParty1;
	PartyMember *selectedParty2;
	PartyMember *selectedParty3;
	PartyMember *selectedParty4;

	virtual bool Ability::Action();
	virtual bool Ability::ReadyAbility();
	virtual bool Ability::ReadyAbility(Enemy * e);
	virtual bool Ability::ReadyAbility(Enemy * e, int enemy);
	virtual bool Ability::ReadyAbility(PartyMember * e);
	virtual bool Ability::ReadyAbility(PartyMember * e, int partyMember);
};

//general abilities
class Attack : public Ability
{
public :
	Mix_Chunk* sHitE;
	int weaponDAM;

	Attack::Attack(PartyMember* p);
	bool Attack::Action();
	bool Attack::ReadyAbility(Enemy * e);
};

class SkipTurn : public Ability
{
public :
	SkipTurn::SkipTurn(PartyMember* p);
	bool SkipTurn::Action();
	bool SkipTurn::ReadyAbility();
};



// Black Mage Spell
class Blizzaga : public Ability
{
public :
	Mix_Chunk* sIce;

	Blizzaga::Blizzaga(PartyMember* p);
	bool Blizzaga::Action();
	bool Blizzaga::ReadyAbility(Enemy * e);
};
// Black Mage Spell
class Death : public Ability
{
public :
	Mix_Chunk* sDeath;

	Death::Death(PartyMember* p);
	bool Death::Action();
	bool Death::ReadyAbility(Enemy * e, int enemy);
};


// White Mage Spell
class Heal : public Ability
{
public :
	Mix_Chunk* sHeal;

	Heal::Heal(PartyMember* p);
	bool Heal::Action();
	bool Heal::ReadyAbility(PartyMember* e);
};
// White Mage Spell
class Lamp : public Ability
{
public :
	Mix_Chunk* sLamp;

	Lamp::Lamp(PartyMember* p);
	bool Lamp::Action();
	bool Lamp::ReadyAbility(Enemy* e);
};


// Red Mage Spell
class SacredFire : public Ability
{
public :
	Mix_Chunk* sFire;

	SacredFire::SacredFire(PartyMember* p);
	bool SacredFire::Action();
	bool SacredFire::ReadyAbility(Enemy* e);
};
// Red Mage Spell
class Fog : public Ability
{
public :
	Mix_Chunk* sFog;

	Fog::Fog(PartyMember* p);
	bool Fog::Action();
	bool Fog::ReadyAbility(PartyMember * e, int partyMember);
};