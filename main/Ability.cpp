#include "Ability.h"

bool Ability::ReadyAbility()
{
	return true;
}
// single target attacks from party members against enemies
bool Ability::ReadyAbility(Enemy * e)
{
	return true;
}
// multi target attacks from party members against enemies
bool Ability::ReadyAbility(Enemy * e, int enemy)
{
	return true;
}
// single target abilities from party members that affect other party members
bool Ability::ReadyAbility(PartyMember * e)
{
	return true;
}
// multi target abilities that from party members that affect all party members
bool Ability::ReadyAbility(PartyMember * e, int partyMember)
{
	return true;
}
bool Ability::Action()
{
	return true;
}