#include "Ability.h"

KickAss::KickAss()
{
	requireEnemy = false;
	name = "Kick Ass";
}
bool KickAss::ReadyAbility()
{
	currentState = 1;
	checkTime = SDL_GetTicks();

	return true;
}
bool KickAss::Action(PartyMember * p)
{
	return true;
}