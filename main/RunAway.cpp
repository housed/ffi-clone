#include "Ability.h"

RunAway::RunAway()
{
	name = "Run Away";
}
bool RunAway::ReadyAbility()
{
	currentState = 1;
	checkTime = SDL_GetTicks();

	return true;
}
bool RunAway::Action(PartyMember * p)
{
	return true;
}