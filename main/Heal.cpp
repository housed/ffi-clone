#include "Ability.h"

Heal::Heal(PartyMember * p)
{
	parent = p;
	name = "Heal";
	requireEnemy = true;
	sHeal = Mix_LoadWAV("./audio/soundfx/spells/heal.wav");
}
bool Heal::ReadyAbility(PartyMember * e)
{
	if (parent->magicPoints > 4)
	{
		parent->magicPoints -= 4;

		currentState = 1;
		checkTime = SDL_GetTicks();
		selectedPartyMember = e;

		return true;
	}
	else
	{
		return false;
	}
}
bool Heal::Action()
{
	switch(currentState)
	{
	case 1:
		currentX = parent->rect.x;
		
		currentState = 2;
		break;
		
	case 2:
		parent->currentAnimation = "Heal";
		Mix_PlayChannel(-1, sHeal, 0);
		parent->rect.x = currentX-30;

		if (checkTime+1000 < (int)SDL_GetTicks())
		{
			checkTime = SDL_GetTicks();
			currentState = 3;
		}
		break;

	case 3:
		parent->rect.x = currentX;
		parent->currentAnimation = "Idle";
		selectedPartyMember->currentAnimation = "Healed";

		if (checkTime+950 < (int)SDL_GetTicks())
		{
			
			if (selectedPartyMember->healthPoints + 5 > selectedPartyMember->maxHealthPoints)
			{
				int i = 0;
				while ((selectedPartyMember->maxHealthPoints != i + selectedPartyMember->healthPoints) || ( i == 4)) 
				{
					i++;
				}
				selectedPartyMember->healthPoints += i;
			}
			else
			{
				selectedPartyMember->healthPoints += 5;
			}
			
			selectedPartyMember->currentAnimation = "Idle";
			parent->turnDone = true;
		}
		break;
	}
	return true;
}