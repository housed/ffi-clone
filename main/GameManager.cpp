#include "GameManager.h"
#include <sstream>
#include <time.h>

SDL_Color colorWhite = { 255, 255, 255 };
bool QUIT = false;
bool ROUNDISOVER = false;

enum TurnState {
	PARTY_TURN = 1,
	ENEMY_TURN,
	END_ROUND
};

GameManager::GameManager()
{
	TURNSTATE = 1;
	Victory = true;

	numOfActiveMembers = 4;

	currentTurn = 0;
	partyMember_selectedAbility = 0;
	partyMember_selectedEnemy = 0;
	partyMember_selectedPartyMember = 0;
	perFormingTurn = false;
	selectEnemy = false;
	selectPartyMember = false;
	selectAllEnemies = false;
	selectAllPartyMembers = false;

	screen = NULL;
	SDL_Init( SDL_INIT_EVERYTHING );
	TTF_Init();

	//////////////////////////////////////
	//////////////////////////////////////
	//////////////////////////////////////
	//ADDED THE LOADING & 
	//PLAYING OF MUSIC
	//////////////////////////////////////
	//////////////////////////////////////
	//////////////////////////////////////
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	music = Mix_LoadMUS("./audio/music/battle_music.wav");
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic( music, -1 );

	SoundA = Mix_LoadWAV("./audio/soundfx/cursor_move.wav");
	SoundB = Mix_LoadWAV("./audio/soundfx/equip.wav");

	mainFont = TTF_OpenFont( "font.TTF", 12 );
	SDL_WM_SetCaption( "Final Fantasy", NULL );

	screen = SDL_SetVideoMode( 488, 364, 32, SDL_SWSURFACE );
}

int main( int argc, char* args[] )
{
	GameManager gameManager;

	gameManager.OnExecute();
	
	return 0;
}

void GameManager::OnExecute() {

	GameManager::AddPartyMember(new Fighter(), "Fighter");
	GameManager::AddPartyMember(new BlackMage(), "Black Mage");
	GameManager::AddPartyMember(new WhiteMage(), "White Mage");
	GameManager::AddPartyMember(new RedMage(), "Red Mage");

	GameManager::CreateEnemyEncounter();

	while(!QUIT)
	{
		if(ROUNDISOVER) {
			SDL_Delay(3000);
			GameManager::CreateEnemyEncounter();
			ROUNDISOVER = false;
		}

		GameManager::drawGame();
	}

	Mix_CloseAudio();

}

void GameManager::AddPartyMember(PartyMember* e, std::string n)
{
	e->rect.x = 375+(party.size()%2)*36;
	e->rect.y = 70+(party.size()*32);
	e->name = n;
	party.push_back(e);
}
void GameManager::CreateEnemyEncounter()
{
	srand ((int)time(NULL));
	int rN = rand() % 3 + 1;

	for(int i = 0; i < rN; i ++)
	{
		int enemyR = rand() % 2;
		switch(enemyR)
		{
		case 0:
			AddEnemy(new WaterNaga());
			break;

		case 1:
			AddEnemy(new NightMare());
			break;
		}
	}
}
void GameManager::AddEnemy(Enemy* e)
{
	e->rect.x = 25+(enemyList.size()%2)*72;
	e->rect.y = 40+(enemyList.size()*52);
	enemyList.push_back(e);
}
void GameManager::drawGame()
{
	SDL_FillRect(screen,NULL,0x000000);

	showimage(0, 0, "./backgrounds/FFI_Background_Ship.png");

	showimage(244, 264, "./gui/battleUI.png");
	showimage(0, 264, "./gui/battleUI.png");

	showPartyMemberStats();
	showEnemyStats();

	for (int i = 0; i < (int)party.size(); i++) { 
		party[i]->animations[party[i]->currentAnimation]->doAnimation(screen, party[i]->rect);
	}

	//MOVED TO FUNCTION GameManager::showPartyMemberStats()
	/*for(int i = 0; i < (int)party.size(); i ++) { 
		party[i]->animations[party[i]->currentAnimation]->doAnimation(screen, party[i]->rect);
		showtext(249, 269, (party[currentTurn]->name));
		showtext(410, 269, ("HP: " + intToChar(party[currentTurn]->healthPoints) + "/" + intToChar(party[currentTurn]->maxHealthPoints)));
		showtext(410, 279, ("MP: " + intToChar(party[currentTurn]->magicPoints) + "/" + intToChar(party[currentTurn]->maxMagicPoints)));*/

	//MOVED TO FUNCTION GameManager::showEnemyStats()
	/*for(int i = 0; i < (int)enemyList.size(); i++) {
		if(enemyList[i]->healthPoints > 0) {
			enemyList[i]->animations[enemyList[i]->currentAnimation]->doAnimation(screen, enemyList[i]->rect);
			showtext(20, 269+(i*20), enemyList[i]->name);
			showtext(185, 269+(i*20), "HP: " + intToChar(enemyList[i]->healthPoints));
		}
		else {
			enemyList.erase (enemyList.begin() + i);
			if(enemyList.size() <= 0)
				TURNSTATE = END_ROUND; //ROUND OVER
		}
	}*/

	if (TURNSTATE == PARTY_TURN) {
		while (party[currentTurn]->dead) {
			currentTurn++;
			if (currentTurn > 3) {
				currentTurn = 0;
				TURNSTATE = ENEMY_TURN;
			}
		}
		if (perFormingTurn) {
			if (party[currentTurn]->turnDone) {
				partyMember_selectedAbility = 0;
				perFormingTurn = false;

				if (currentTurn < (int)party.size()-1) {
					currentTurn += 1;
				}
				else {
					currentTurn = 0;
					TURNSTATE = ENEMY_TURN;
				}

				perFormingTurn = false;
			}
			else {
				party[currentTurn]->abilities[partyMember_selectedAbility]->Action();
			}
		}
		else {
			if ((!selectEnemy) && (!selectPartyMember) && (!selectAllEnemies) && (!selectAllPartyMembers))
			{
				GameManager::displayAbilities(party[currentTurn]);
			}
			else {
				//   single PARTY MEMBER SELECTION!!!
				if ( selectPartyMember ) {
					showimage(party[partyMember_selectedPartyMember]->rect.x+(party[partyMember_selectedPartyMember]->animations[party[partyMember_selectedPartyMember]->currentAnimation]->entity->surface->w)/2-16, party[partyMember_selectedPartyMember]->rect.y-32, "./gui/enemyCursor.png");

					int keyPress = input.keyPress();
					if (keyPress == SDLK_RIGHT) {
						partyMember_selectedPartyMember = (partyMember_selectedPartyMember+1 > (int)party.size()-1 ? 0:partyMember_selectedPartyMember+1);
					}
					if (keyPress == SDLK_LEFT) {
						partyMember_selectedPartyMember = (partyMember_selectedPartyMember-1 < 0 ? (int)party.size()-1:partyMember_selectedPartyMember-1);
					}
					if (keyPress == SDLK_RETURN) {
						if (party[currentTurn]->abilities[partyMember_selectedAbility]->ReadyAbility(party[partyMember_selectedPartyMember])) {
							selectPartyMember = false;
							party[currentTurn]->turnDone = false;
							perFormingTurn = true;
						}
						else {
							selectEnemy = false;
						}
					}

					if (keyPress == SDL_QUIT)
						QUIT = true;

				} // multi enemy selection
				else if ( selectAllEnemies == true ) {
					int j = (int)enemyList.size();
					
					partyMember_selectedEnemy = 0;
						
					if (j == 1) {
						showimage(enemyList[partyMember_selectedEnemy]->rect.x+(enemyList[partyMember_selectedEnemy]->animations[enemyList[partyMember_selectedEnemy]->currentAnimation]->entity->surface->w)/2-16, enemyList[partyMember_selectedEnemy]->rect.y-32, "./gui/enemyCursor.png");
					}
					else if (j == 2) {
						showimage(enemyList[partyMember_selectedEnemy]->rect.x+(enemyList[partyMember_selectedEnemy]->animations[enemyList[partyMember_selectedEnemy]->currentAnimation]->entity->surface->w)/2-16, enemyList[partyMember_selectedEnemy]->rect.y-32, "./gui/enemyCursor.png");
						showimage(enemyList[partyMember_selectedEnemy+1]->rect.x+(enemyList[partyMember_selectedEnemy+1]->animations[enemyList[partyMember_selectedEnemy+1]->currentAnimation]->entity->surface->w)/2-16, enemyList[partyMember_selectedEnemy+1]->rect.y-32, "./gui/enemyCursor.png");
					}
					else if (j == 3) {
						showimage(enemyList[partyMember_selectedEnemy]->rect.x+(enemyList[partyMember_selectedEnemy]->animations[enemyList[partyMember_selectedEnemy]->currentAnimation]->entity->surface->w)/2-16, enemyList[partyMember_selectedEnemy]->rect.y-32, "./gui/enemyCursor.png");
						showimage(enemyList[partyMember_selectedEnemy+1]->rect.x+(enemyList[partyMember_selectedEnemy+1]->animations[enemyList[partyMember_selectedEnemy+1]->currentAnimation]->entity->surface->w)/2-16, enemyList[partyMember_selectedEnemy+1]->rect.y-32, "./gui/enemyCursor.png");
						showimage(enemyList[partyMember_selectedEnemy+2]->rect.x+(enemyList[partyMember_selectedEnemy+2]->animations[enemyList[partyMember_selectedEnemy+2]->currentAnimation]->entity->surface->w)/2-16, enemyList[partyMember_selectedEnemy+2]->rect.y-32, "./gui/enemyCursor.png");
					}
					else {
						showimage(enemyList[partyMember_selectedEnemy]->rect.x+(enemyList[partyMember_selectedEnemy]->animations[enemyList[partyMember_selectedEnemy]->currentAnimation]->entity->surface->w)/2-16, enemyList[partyMember_selectedEnemy]->rect.y-32, "./gui/enemyCursor.png");
						showimage(enemyList[partyMember_selectedEnemy+1]->rect.x+(enemyList[partyMember_selectedEnemy+1]->animations[enemyList[partyMember_selectedEnemy+1]->currentAnimation]->entity->surface->w)/2-16, enemyList[partyMember_selectedEnemy+1]->rect.y-32, "./gui/enemyCursor.png");
						showimage(enemyList[partyMember_selectedEnemy+2]->rect.x+(enemyList[partyMember_selectedEnemy+2]->animations[enemyList[partyMember_selectedEnemy+2]->currentAnimation]->entity->surface->w)/2-16, enemyList[partyMember_selectedEnemy+2]->rect.y-32, "./gui/enemyCursor.png");
						showimage(enemyList[partyMember_selectedEnemy+3]->rect.x+(enemyList[partyMember_selectedEnemy+3]->animations[enemyList[partyMember_selectedEnemy+3]->currentAnimation]->entity->surface->w)/2-16, enemyList[partyMember_selectedEnemy+3]->rect.y-32, "./gui/enemyCursor.png");
					}
							

					int keyPress = input.keyPress();
					if (keyPress == SDLK_RETURN) {
						int enemies = 0;
						int enemyNumber = 0;

						while (enemies < j) {
							enemies++;
							party[currentTurn]->abilities[partyMember_selectedAbility]->ReadyAbility(enemyList[partyMember_selectedEnemy + enemyNumber], enemies);
							enemyNumber++;
						}

						if (enemies == j) {
							selectAllEnemies = false;
							party[currentTurn]->turnDone = false;
							perFormingTurn = true;
						}
						else {
							selectEnemy = false;
						}
					}

					if (keyPress == SDL_QUIT)
						QUIT = true;

				}    //  multi party member selection
				else if ( selectAllPartyMembers == true )
				{
					int g = (int)party.size();
					
					partyMember_selectedPartyMember = 0;
						
					if (g == 1) {
						showimage(party[partyMember_selectedPartyMember]->rect.x+(party[partyMember_selectedPartyMember]->animations[party[partyMember_selectedPartyMember]->currentAnimation]->entity->surface->w)/2-16, party[partyMember_selectedPartyMember]->rect.y-32, "./gui/enemyCursor.png");
					}
					else if (g == 2) {
						showimage(party[partyMember_selectedPartyMember]->rect.x+(party[partyMember_selectedPartyMember]->animations[party[partyMember_selectedPartyMember]->currentAnimation]->entity->surface->w)/2-16, party[partyMember_selectedPartyMember]->rect.y-32, "./gui/enemyCursor.png");
						showimage(party[partyMember_selectedPartyMember+1]->rect.x+(party[partyMember_selectedPartyMember+1]->animations[party[partyMember_selectedPartyMember+1]->currentAnimation]->entity->surface->w)/2-16, party[partyMember_selectedPartyMember+1]->rect.y-32, "./gui/enemyCursor.png");
					}
					else if (g == 3) {
						showimage(party[partyMember_selectedPartyMember]->rect.x+(party[partyMember_selectedPartyMember]->animations[party[partyMember_selectedPartyMember]->currentAnimation]->entity->surface->w)/2-16, party[partyMember_selectedPartyMember]->rect.y-32, "./gui/enemyCursor.png");
						showimage(party[partyMember_selectedPartyMember+1]->rect.x+(party[partyMember_selectedPartyMember+1]->animations[party[partyMember_selectedPartyMember+1]->currentAnimation]->entity->surface->w)/2-16, party[partyMember_selectedPartyMember+1]->rect.y-32, "./gui/enemyCursor.png");
						showimage(party[partyMember_selectedPartyMember+2]->rect.x+(party[partyMember_selectedPartyMember+2]->animations[party[partyMember_selectedPartyMember+2]->currentAnimation]->entity->surface->w)/2-16, party[partyMember_selectedPartyMember+2]->rect.y-32, "./gui/enemyCursor.png");
					}
					else {
						showimage(party[partyMember_selectedPartyMember]->rect.x+(party[partyMember_selectedPartyMember]->animations[party[partyMember_selectedPartyMember]->currentAnimation]->entity->surface->w)/2-16, party[partyMember_selectedPartyMember]->rect.y-32, "./gui/enemyCursor.png");
						showimage(party[partyMember_selectedPartyMember+1]->rect.x+(party[partyMember_selectedPartyMember+1]->animations[party[partyMember_selectedPartyMember+1]->currentAnimation]->entity->surface->w)/2-16, party[partyMember_selectedPartyMember+1]->rect.y-32, "./gui/enemyCursor.png");
						showimage(party[partyMember_selectedPartyMember+2]->rect.x+(party[partyMember_selectedPartyMember+2]->animations[party[partyMember_selectedPartyMember+2]->currentAnimation]->entity->surface->w)/2-16, party[partyMember_selectedPartyMember+2]->rect.y-32, "./gui/enemyCursor.png");
						showimage(party[partyMember_selectedPartyMember+3]->rect.x+(party[partyMember_selectedPartyMember+3]->animations[party[partyMember_selectedPartyMember+3]->currentAnimation]->entity->surface->w)/2-16, party[partyMember_selectedPartyMember+3]->rect.y-32, "./gui/enemyCursor.png");
					}
							

					int keyPress = input.keyPress();
					if (keyPress == SDLK_RETURN)
					{
						int partyAlive = 0;
						int partySize = 0;
						while (partyAlive < g)
						{
							partyAlive++;
							party[currentTurn]->abilities[partyMember_selectedAbility]->ReadyAbility(party[partyMember_selectedPartyMember + partySize], partyAlive);
							partySize++;
						}
						if (partyAlive == g)
						{
							selectAllPartyMembers = false;
							party[currentTurn]->turnDone = false;
							perFormingTurn = true;
						}
						else
						{
							selectEnemy = false;
						}
					}
					if (keyPress == SDL_QUIT)
						QUIT = true;
				}
				else   //  single enemy selection
				{
					showimage(enemyList[partyMember_selectedEnemy]->rect.x+(enemyList[partyMember_selectedEnemy]->animations[enemyList[partyMember_selectedEnemy]->currentAnimation]->entity->surface->w)/2-16, enemyList[partyMember_selectedEnemy]->rect.y-32, "./gui/enemyCursor.png");

					int keyPress = input.keyPress();
					if (keyPress == SDLK_RIGHT)
					{
						partyMember_selectedEnemy = (partyMember_selectedEnemy+1 > (int)enemyList.size()-1 ? 0:partyMember_selectedEnemy+1);
					}
					if (keyPress == SDLK_LEFT)
					{
						partyMember_selectedEnemy = (partyMember_selectedEnemy-1 < 0 ? (int)enemyList.size()-1:partyMember_selectedEnemy-1);
					}
					if (keyPress == SDLK_RETURN)
					{
						if (party[currentTurn]->abilities[partyMember_selectedAbility]->ReadyAbility(enemyList[partyMember_selectedEnemy]))
						{
							selectEnemy = false;
							party[currentTurn]->turnDone = false;
							perFormingTurn = true;
						}
						else
						{
							selectEnemy = false;
						}
					}
					if (keyPress == SDL_QUIT)
						QUIT = true;
				}
			}
		}
	}
	else if (TURNSTATE == ENEMY_TURN)
	{
		int keyPress = input.keyPress();

		if (enemyList.size()-1 < currentTurn)
			currentTurn = 0;

		if (perFormingTurn)
		{
			if (enemyList[currentTurn]->turnDone)
			{
				enemy_selectedAbility = 0;
				perFormingTurn = false;
				if (currentTurn < (int)enemyList.size()-1)
				{
					currentTurn += 1;
				}
				else
				{
					currentTurn = 0;
					TURNSTATE = 1;
				}
				perFormingTurn = false;
			}
			else {
				enemyList[currentTurn]->abilities[enemy_selectedAbility]->Action(enemyList[currentTurn]);
			}
		}
		else
		{
			srand ((int)time(NULL));
			enemyList[currentTurn]->turnDone = false;
			enemy_selectedAbility = rand() % enemyList[currentTurn]->abilities.size();
			enemyList[currentTurn]->abilities[enemy_selectedAbility]->ReadyAbility(party);
			perFormingTurn = true;
		}

		if (keyPress == SDL_QUIT)
			QUIT = true;
	}
	else if (TURNSTATE == END_ROUND) {
		onRoundWin();
		onRoundLose();
	}


	SDL_Flip( screen );
	SDL_Delay(1000/60);
}

void GameManager::displayAbilities(Entity* e)
{
	PartyMember* tempMember;
	tempMember = (PartyMember*)(e);
	int keyPress = input.keyPress();
	if (keyPress == SDLK_UP)
	{
		partyMember_selectedAbility = (partyMember_selectedAbility > 0 ? partyMember_selectedAbility-1:0);
		Mix_PlayChannel(-1, SoundA, 0); //PLAY SOUND
	}
	if (keyPress == SDLK_DOWN)
	{
		partyMember_selectedAbility = (partyMember_selectedAbility < (int)tempMember->abilities.size()-1 ? partyMember_selectedAbility+1:tempMember->abilities.size()-1);
		Mix_PlayChannel(-1, SoundA, 0); //PLAY SOUND
	}
	if (keyPress == SDLK_RETURN)
	{
		Mix_PlayChannel(-1, SoundB, 0); //PLAY SOUND

		if (tempMember->abilities[partyMember_selectedAbility]->requireEnemy)
		{
			partyMember_selectedEnemy = 0;
			if (tempMember->name == "White Mage")
			{
				if (tempMember->abilities[partyMember_selectedAbility]->name == "Heal")
					selectPartyMember = true;
				else
					selectEnemy = true;
			}
			else if (tempMember->name == "Black Mage")
			{
				if (tempMember->abilities[partyMember_selectedAbility]->name == "Death")
					selectAllEnemies = true;
				else
					selectEnemy = true;
			}
			else if (tempMember->name == "Red Mage")
			{
				if (tempMember->abilities[partyMember_selectedAbility]->name == "Fog")
					selectAllPartyMembers = true;
				else
					selectEnemy = true;
			}
			else
			{
				selectEnemy = true;
			}
		}
		else {
			if (tempMember->abilities[partyMember_selectedAbility]->ReadyAbility())
			{
				selectEnemy = false;
				selectAllEnemies = false;
				selectAllPartyMembers = false;
				tempMember->turnDone = false;
				perFormingTurn = true;
			}
		}
		return;
	}
	if (keyPress == SDL_QUIT)
		QUIT = true;

	for(int i = 0; i < (int)tempMember->abilities.size(); i ++)
	{
		if (partyMember_selectedAbility == i)
		{
			showimage(253, 292+(i*20), "./gui/cursor.png");
		}

		showtext(285, 297+(i*20), tempMember->abilities[i]->name);
	}
}

void GameManager::showtext(int x, int y, std::string msg)
{
	SDL_Surface *message = TTF_RenderText_Solid( mainFont, msg.c_str(), colorWhite );
	SDL_Rect msgLocation;
	msgLocation.x = x;
	msgLocation.y = y;
	SDL_BlitSurface( message, NULL, screen, &msgLocation );
	SDL_FreeSurface( message );
}

void GameManager::showimage(int x, int y, std::string img)
{
	Entity image;
	image.SetSurfaceImage((char*)(img.c_str()));
	image.rect.x = x;
	image.rect.y = y;

	SDL_BlitSurface( image.surface, NULL, screen, &image.rect );
	SDL_FreeSurface( image.surface );
}

void GameManager::showPartyMemberStats() {
	showtext(249, 269, (party[currentTurn]->name));
	showtext(410, 269, ("HP: " + intToChar(party[currentTurn]->healthPoints) + "/" + intToChar(party[currentTurn]->maxHealthPoints)));
	showtext(410, 279, ("MP: " + intToChar(party[currentTurn]->magicPoints) + "/" + intToChar(party[currentTurn]->maxMagicPoints)));

	checkPartyList();
}

void GameManager::showEnemyStats() {
	for(int i = 0; i < (int)enemyList.size(); i++) {
		if(enemyList[i]->healthPoints > 0) {
			enemyList[i]->animations[enemyList[i]->currentAnimation]->doAnimation(screen, enemyList[i]->rect);
			showtext(20, 269+(i*20), enemyList[i]->name);
			showtext(185, 269+(i*20), "HP: " + intToChar(enemyList[i]->healthPoints));
		}
		else {
			enemyList.erase (enemyList.begin() + i);
			if(enemyList.size() <= 0)
				TURNSTATE = END_ROUND; //ROUND OVER
		}
	}
}

void GameManager::checkPartyList() {
	if(party[0]->dead == true && party[1]->dead == true && party[2]->dead == true && party[3]->dead == true) {
		Victory = false;
		TURNSTATE = END_ROUND;
	}
}

void GameManager::onRoundWin() {
	if (Victory) {
		showtext(10, 10, "YOU WIN!");

		ROUNDISOVER = true;

		TURNSTATE = 1;
		perFormingTurn = false;
		currentTurn = 0;
		selectEnemy = false;
		partyMember_selectedAbility = 0;
		partyMember_selectedEnemy = 0;
	}
	else {
		return;
	}
}

void GameManager::onRoundLose() {
	int keyPress = input.keyPress();

	if(!Victory) {
		showtext(10, 10, "YOU LOSE!");

		showimage(0, 0, "./backgrounds/FFI_Background_Ship_LOSE.png");

		for(int i = 0; i < party.size(); i++) {
			party[i]->currentAnimation = "Lose";
			party[i]->animations[party[i]->currentAnimation]->doAnimation(screen, party[i]->rect);

			if (keyPress == SDL_QUIT)
				QUIT = true;
		}
	}
	else {
		return;
	}
}

std::string GameManager::intToChar(int m)
{
	std::stringstream s;
	s << m;
	std::string st = s.str();

	return st;
}