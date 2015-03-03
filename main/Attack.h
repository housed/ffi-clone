#pragma once

#include "Ability.h"
#include "PartyMember.h"

class Attack : public Ability
{
public :
	Attack::Attack();
	bool Attack::Action(PartyMember * p);
	bool Attack::ReadyAbility(Enemy * e);
};