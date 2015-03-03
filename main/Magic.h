#pragma once

#include "Ability.h"
#include "PartyMember.h"

class Magic : public Ability
{
public :
	Magic::Magic();
	bool Magic::Action(PartyMember * p);
	bool Magic::ReadyAbility(Enemy * e);
};