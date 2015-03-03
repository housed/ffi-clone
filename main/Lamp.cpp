#include "Ability.h"

Lamp::Lamp(PartyMember * p)
{
	parent = p;
	name = "Lamp";
	requireEnemy = true;
	sLamp = Mix_LoadWAV("./audio/soundfx/spells/lamp.wav");
}
bool Lamp::ReadyAbility(Enemy * e)
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
bool Lamp::Action()
{
	switch(currentState)
	{
	case 1:
		currentX = parent->rect.x;
		
		currentState = 2;
		break;
		
	case 2:
		Mix_PlayChannel(-1, sLamp, 0);
		parent->currentAnimation = "Lamp";
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