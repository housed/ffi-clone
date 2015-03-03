#pragma once
#include "PartyMember.h"
#include <string>

class PartyMember;

class Weapons
{
public:

	std::string weaponName;
	int weaponDMG;
};



class Sword : public Weapons
{
public:

	Sword::Sword(PartyMember * p)
	{
		weaponName = "Sword";
		weaponDMG = 12;
	}
};
