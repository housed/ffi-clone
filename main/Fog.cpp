#include "Ability.h"

Fog::Fog(PartyMember * p)
{
	parent = p;
	name = "Fog";
	requireEnemy = true;
	sFog = Mix_LoadWAV("./audio/soundfx/spells/fog.wav");
}
bool Fog::ReadyAbility(PartyMember * e, int partyMember)
{
	partyMembers = partyMember;
	if (parent->magicPoints > 4)
	{
		if (partyMembers == 1)
		{
			parent->magicPoints -= 4;
			currentState = 1;
		}
		
		checkTime = SDL_GetTicks();

		switch(partyMembers)
		{
		case 1 :	selectedParty1 = e;
			return false;
			break;
		case 2 :	selectedParty2 = e;
			return false;
			break;
		case 3 :	selectedParty3 = e;
			return false;
			break;
		case 4 :	selectedParty4 = e;
			return true;
			break;
		}

	}
	else
	{
		return false;
	}
}
bool Fog::Action()
{
	switch(currentState)
	{
	case 1:
		currentX = parent->rect.x;
		
		currentState = 2;
		break;
		
	case 2:
		Mix_PlayChannel(-1, sFog, 0);
		parent->currentAnimation = "Fog";
		parent->rect.x = currentX-30;

		if (checkTime+1600 < (int)SDL_GetTicks())
		{
			checkTime = SDL_GetTicks();
			currentState = 3;
		}
		break;

	case 3:
		parent->rect.x = currentX;
		parent->currentAnimation = "Idle";
		/*
		if (partyMembers == 1)
		{
			selectedParty1->currentAnimation = "Idle";
		}
		else if (partyMembers == 2)
		{
			selectedParty1->currentAnimation = "Idle";
			selectedParty2->currentAnimation = "Idle";
		}
		else if (partyMembers == 3)
		{
			selectedParty1->currentAnimation = "Idle";
			selectedParty2->currentAnimation = "Idle";
			selectedParty3->currentAnimation = "Idle";
		}
		else
		{
			selectedParty1->currentAnimation = "Idle";
			selectedParty2->currentAnimation = "Idle";
			selectedParty3->currentAnimation = "Idle";
			selectedParty4->currentAnimation = "Idle";
		}  */


		// animation will eventually be some type of fog or magical effect going around the party members

		if (checkTime+500 < (int)SDL_GetTicks())
		{
			if (enemies == 1)
			{
				selectedParty1->evasive = true;
				//selectedParty1->currentAnimation = "Idle";
			}
			else if (enemies == 2)
			{
				selectedParty1->evasive = true;
				selectedParty2->evasive = true;
				//selectedParty1->currentAnimation = "Idle";
				//selectedParty2->currentAnimation = "Idle";
			}
			else if (enemies == 3)
			{
				selectedParty1->evasive = true;
				selectedParty2->evasive = true;
				selectedParty3->evasive = true;
				//selectedParty1->currentAnimation = "Idle";
				//selectedParty2->currentAnimation = "Idle";
				//selectedParty3->currentAnimation = "Idle";
			}
			else
			{
				selectedParty1->evasive = true;
				selectedParty2->evasive = true;
				selectedParty3->evasive = true;
				selectedParty4->evasive = true;
				//selectedParty1->currentAnimation = "Idle";
				//selectedParty2->currentAnimation = "Idle";
				//selectedParty3->currentAnimation = "Idle";
				//selectedParty4->currentAnimation = "Idle";
			}

			parent->turnDone = true;
		}
		break;
	}
	return true;
}