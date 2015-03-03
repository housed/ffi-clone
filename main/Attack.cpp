#include "Ability.h"

Attack::Attack(PartyMember * p)
{
	name = "Attack";
	parent = p;
	parent->weaponEquipped = parent->weapons[0]->weaponName;
	weaponDAM = parent->weapons[0]->weaponDMG;
	requireEnemy = true;
	sHitE = Mix_LoadWAV("./audio/soundfx/hitE.wav");
}
bool Attack::ReadyAbility(Enemy * e)
{
	currentState = 1;
	checkTime = SDL_GetTicks();
	currentX = 0;
	currentY = 0;
	selectedEnemy = e;

	return true;
}
bool Attack::Action()
{
	switch(currentState)
	{
	case 1:
		parent->currentAnimation = "Walk";
		currentX = parent->rect.x;
		currentY = parent->rect.y;

		currentState = 2;
		checkTime = SDL_GetTicks();
		break;

	case 2:
		if (parent->rect.x > currentX-50)
		{
			if (checkTime+35 < (int)SDL_GetTicks())
			{
				checkTime = SDL_GetTicks();
				parent->rect.x -= 10;
			}
		}
		else
		{
			currentState = 3;
		}
		break;

	case 3:
		Mix_PlayChannel(-1, sHitE, 0);
		parent->currentAnimation = parent->weaponEquipped;
		checkTime = SDL_GetTicks();
		currentState = 4;
		break;

	case 4:
		if (checkTime+500 < (int)SDL_GetTicks())
		{
			selectedEnemy->currentAnimation = "Hurt";
			selectedEnemy->healthPoints -= weaponDAM;

			parent->currentAnimation = "Walk";
			currentState = 5;
			checkTime = SDL_GetTicks();
		}
		break;

	case 5:
		if (parent->rect.x < currentX)
		{
			if (checkTime+35 < (int)SDL_GetTicks())
			{
				checkTime = SDL_GetTicks();
				parent->rect.x += 10;
			}
		}
		else
		{
			parent->rect.y = currentY;
			parent->rect.x = currentX;
			parent->currentAnimation = "Idle";
			if (checkTime+500 < (int)SDL_GetTicks())
			{
				selectedEnemy->currentAnimation = "Idle";
				parent->turnDone = true;
			}
		}
		break;
	}

	return true;
}