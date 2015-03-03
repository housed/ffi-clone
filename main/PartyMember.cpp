#include "PartyMember.h"

PartyMember::PartyMember()
{
	name = "";
	healthPoints = 100;
	maxHealthPoints = 100;
	magicPoints = 100;
	maxMagicPoints = 100;
	evasive = false;
	dead = false;
	turnDone = false;
	currentAnimation = "Idle";
}
void PartyMember::AddAnimation(std::string n, Animation *a)
{
	animations[n] = a;
}