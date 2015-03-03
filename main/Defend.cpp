#include "Ability.h"

Defend::Defend()
{
	name = "Defend";
}
bool Defend::ReadyAbility()
{
	currentState = 1;
	checkTime = SDL_GetTicks();

	return true;
}
bool Defend::Action(PartyMember * p)
{
	return true;
}