#include "EnemyAbility.h"
#include <time.h>

EnemyAttack::EnemyAttack()
{
	
}
bool EnemyAttack::ReadyAbility(std::vector<PartyMember*> p)
{
	sHit = Mix_LoadWAV("./audio/soundfx/hit1.wav");
	srand ((int)time(NULL));

	currentState = 1;
	selectedParty = p[rand() % p.size()];

	while(selectedParty->dead == true)
		selectedParty = p[rand() % p.size()];

	return true;
}
bool EnemyAttack::Action(Enemy * e)
{
	switch(currentState)
	{
	case 1:
		currentX = e->rect.x;
		checkTime = SDL_GetTicks();
		move_dir = 1;

		currentState = 2;
		break;

	case 2:
		if (move_dir)
		{
			e->rect.x += 5;
			if (e->rect.x > currentX+10)
			{
				move_dir = 0;
			}
		}
		else
		{
			e->rect.x -= 5;
			if (e->rect.x < currentX-10)
			{
				move_dir = 1;
			}
		}
		if (checkTime+1000 < (int)SDL_GetTicks())
		{
			int evasionSuccess = ((rand() % 101) + (rand() % 101) + (rand() % 101))/3;
			
			if ((selectedParty->evasive == true) && (evasionSuccess <= 65))
			{
				// to be evade later on (probly character moving back and forth)
				selectedParty->currentAnimation = "Dodge";
			}
			else if ((selectedParty->healthPoints - 25) <= 0)
			{
				selectedParty->currentAnimation = "Dieing";
				selectedParty->dead = true;
			}
			else
			{
				selectedParty->evasive = false;
				Mix_PlayChannel(-1, sHit, 0);
				selectedParty->currentAnimation = "Hurt";
			}
			checkTime = SDL_GetTicks();
			currentState = 3;
		}
		break;

	case 3:
		e->rect.x = currentX;
		if (checkTime+500 < (int)SDL_GetTicks())
		{
			if (selectedParty->evasive == true)
			{
				selectedParty->healthPoints -= 0;
			}
			else
			{
				selectedParty->healthPoints -= 25;
			}
			
			if (selectedParty->dead == true)
			{
				selectedParty->currentAnimation = "Dead";
			}
			else
			{
				selectedParty->currentAnimation = "Idle";
			}

			// evasive only lasts once after spell fog regardless of if it worked
			selectedParty->evasive = false;
			e->turnDone = true;
		}
		break;
	}
	return true;
}