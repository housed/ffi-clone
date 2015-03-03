#include "Ability.h"

Magic::Magic(PartyMember * p)
{
	parent = p;
	name = "Some Random magic Spell";
	requireEnemy = true;
}
bool Magic::ReadyAbility(Enemy * e)
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
bool Magic::Action()
{
	switch(currentState)
	{
	case 1:
		currentX = parent->rect.x;
		
		currentState = 2;
		break;
		
	case 2:
		parent->currentAnimation = "Magic";
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
			selectedEnemy->healthPoints -= 7;
			selectedEnemy->currentAnimation = "Idle";
			parent->turnDone = true;
		}
		break;
	}
	return true;
}