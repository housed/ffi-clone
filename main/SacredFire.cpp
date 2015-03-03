#include "Ability.h"

SacredFire::SacredFire(PartyMember * p)
{
	parent = p;
	name = "Sacred Fire";
	requireEnemy = true;
	sFire = Mix_LoadWAV("./audio/soundfx/spells/fire.wav");
}
bool SacredFire::ReadyAbility(Enemy * e)
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
bool SacredFire::Action()
{
	switch(currentState)
	{
	case 1:
		currentX = parent->rect.x;
		
		currentState = 2;
		break;
		
	case 2:
		Mix_PlayChannel(-1, sFire, 0);
		parent->currentAnimation = "Sacred Fire";
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
		selectedEnemy->currentAnimation = "Hurt";

		if (checkTime+500 < (int)SDL_GetTicks())
		{
			selectedEnemy->healthPoints -= 20;
			selectedEnemy->currentAnimation = "Idle";
			parent->turnDone = true;
		}
		break;
	}
	return true;
}