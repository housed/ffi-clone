#pragma once

#include "Ability.h"
#include "PartyMember.h"

class RunAway : public Ability
{
public :
	RunAway::RunAway();
	bool RunAway::Action(PartyMember * p);
	bool RunAway::ReadyAbility();
};