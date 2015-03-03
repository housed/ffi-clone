#include "Ability.h"

Blizzaga::Blizzaga(PartyMember * p)
{
	parent = p;
	name = "Blizzaga";
	requireEnemy = true;
	sIce = Mix_LoadWAV("./audio/soundfx/spells/ice.wav");
}
bool Blizzaga::ReadyAbility(Enemy * e)
{
	if (parent->magicPoints > 4)
	{
		parent->magicPoints -= 4;

		currentState = 1;
		checkTime = SDL_GetTicks();
		selectedEnemy = e;

		return true;
	}
	else
	{
		return false;
	}
}
bool Blizzaga::Action()
{
	switch(currentState)
	{
	case 1:
		currentX = parent->rect.x;
		
		currentState = 2;
		break;
		
	case 2:
		Mix_PlayChannel(-1, sIce, 0);
		parent->currentAnimation = "Blizzaga";
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
		selectedEnemy->currentAnimation = "Hurt";

		if (checkTime+500 < (int)SDL_GetTicks())
		{
			selectedEnemy->healthPoints -= 7;
			selectedEnemy->currentAnimation = "Idle";
			parent->turnDone = true;
		}
		break;
	}
	return true;
}