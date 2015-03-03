#pragma once

#include "Ability.h"
#include "PartyMember.h"

class Defend : public Ability
{
public :
	Defend::Defend();
	bool Defend::Action(PartyMember * p);
	bool Defend::ReadyAbility();
};