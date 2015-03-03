#include "Ability.h"

Death::Death(PartyMember * p)
{
	parent = p;
	name = "Death";
	requireEnemy = true;
	sDeath = Mix_LoadWAV("./audio/soundfx/spells/death.wav");
}
bool Death::ReadyAbility(Enemy * e, int enemy)
{
	enemies = enemy;
	if (parent->magicPoints > 4)
	{
		if (enemy == 1)
		{
			parent->magicPoints -= 4;
			currentState = 1;
		}
		
		checkTime = SDL_GetTicks();

		switch(enemy)
		{
		case 1 :	selectedEnemy1 = e;
			return false;
			break;
		case 2 :	selectedEnemy2 = e;
			return false;
			break;
		case 3 :	selectedEnemy3 = e;
			return false;
			break;
		case 4 :	selectedEnemy4 = e;
			return true;
			break;
		}

	}
	else
	{
		return false;
	}
}
bool Death::Action()
{
	switch(currentState)
	{
	case 1:
		currentX = parent->rect.x;
		currentState = 2;
		break;
		
	case 2:
		parent->currentAnimation = "Death";
		Mix_PlayChannel(-1, sDeath, 0);
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

		if (enemies == 1)
		{
			selectedEnemy1->currentAnimation = "Hurt";
		}
		else if (enemies == 2)
		{
			selectedEnemy1->currentAnimation = "Hurt";
			selectedEnemy2->currentAnimation = "Hurt";
		}
		else if (enemies == 3)
		{
			selectedEnemy1->currentAnimation = "Hurt";
			selectedEnemy2->currentAnimation = "Hurt";
			selectedEnemy3->currentAnimation = "Hurt";
		}
		else
		{
			selectedEnemy1->currentAnimation = "Hurt";
			selectedEnemy2->currentAnimation = "Hurt";
			selectedEnemy3->currentAnimation = "Hurt";
			selectedEnemy4->currentAnimation = "Hurt";
		}

		if (checkTime+500 < (int)SDL_GetTicks())
		{
			if (enemies == 1)
			{
				selectedEnemy1->healthPoints -= 20;
				selectedEnemy1->currentAnimation = "Idle";
			}
			else if (enemies == 2)
			{
				selectedEnemy1->healthPoints -= 20;
				selectedEnemy2->healthPoints -= 20;
				selectedEnemy1->currentAnimation = "Idle";
				selectedEnemy2->currentAnimation = "Idle";
			}
			else if (enemies == 3)
			{
				selectedEnemy1->healthPoints -= 20;
				selectedEnemy2->healthPoints -= 20;
				selectedEnemy3->healthPoints -= 20;
				selectedEnemy1->currentAnimation = "Idle";
				selectedEnemy2->currentAnimation = "Idle";
				selectedEnemy3->currentAnimation = "Idle";
			}
			else
			{
				selectedEnemy1->healthPoints -= 20;
				selectedEnemy2->healthPoints -= 20;
				selectedEnemy3->healthPoints -= 20;
				selectedEnemy4->healthPoints -= 20;
				selectedEnemy1->currentAnimation = "Idle";
				selectedEnemy2->currentAnimation = "Idle";
				selectedEnemy3->currentAnimation = "Idle";
				selectedEnemy4->currentAnimation = "Idle";
			}

			parent->turnDone = true;
		}
		break;
	}
	return true;
}