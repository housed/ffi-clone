#pragma once

#include "Ability.h"
#include "PartyMember.h"

class KickAss : public Ability
{
public :
	KickAss::KickAss();
	bool KickAss::Action(PartyMember * p);
	bool KickAss::ReadyAbility();
};