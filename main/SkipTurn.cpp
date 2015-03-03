#include "Ability.h"

SkipTurn::SkipTurn(PartyMember * p)
{
	parent = p;
	name = "Skip Turn";
	requireEnemy = false;
}
bool SkipTurn::ReadyAbility()
{
	return true;
}
bool SkipTurn::Action()
{
	parent->turnDone = true;

	return true;
}