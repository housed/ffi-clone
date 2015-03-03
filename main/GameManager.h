#pragma once
#include <vector>
#include "Entity.h"
#include "PartyMember.h"
#include "FullPartyMembers.h"
#include "FullEnemyList.h"
#include "Enemy.h"
#include "UserInput.h"
#include "SDL_Mixer.h"

class GameManager
{
public:
	std::vector<PartyMember*> party;
	std::vector<Enemy*> enemyList;
	std::vector<Entity> generalDraw;

	int numOfActiveMembers;

	bool ActiveParty;

	UserInput input;

	SDL_Surface* screen;
	
	TTF_Font* mainFont;
	
	Mix_Music* music;
	Mix_Chunk* SoundA;
	Mix_Chunk* SoundB;

	int TURNSTATE;
	bool Victory;
	
	int currentTurn;
	int partyMember_selectedAbility;
	int partyMember_selectedEnemy;
	int partyMember_selectedPartyMember;
	int enemy_selectedAbility;
	bool perFormingTurn;
	bool selectEnemy;
	bool selectPartyMember;
	bool selectAllEnemies;
	bool selectAllPartyMembers;

	GameManager::GameManager();
	void GameManager::OnExecute();
	void GameManager::drawGame();
	void GameManager::AddPartyMember(PartyMember* e, std::string n);
	void GameManager::AddEnemy(Enemy* e);
	void GameManager::CreateEnemyEncounter();
	void GameManager::displayAbilities(Entity* e);
	void GameManager::showPartyMemberStats();
	void GameManager::showEnemyStats();
	void GameManager::prepareNewRound();
	void GameManager::checkPartyList();
	void GameManager::checkEnemyList(int i);
	void GameManager::onRoundWin();
	void GameManager::onRoundLose();

	void GameManager::showtext(int x, int y, std::string msg);
	void GameManager::showimage(int x, int y, std::string img);
	std::string GameManager::intToChar(int m);
};