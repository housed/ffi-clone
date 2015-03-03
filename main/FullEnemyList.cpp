#include "FullEnemyList.h"

WaterNaga::WaterNaga()
{
	name = "Water Naga";
	maxHealthPoints = healthPoints = 50;
	maxMagicPoints = magicPoints = 0;
	imageWidth = 92;
	imageHeight = 98;

	abilities.push_back(new EnemyAttack());

	AddAnimation("Idle", new Animation(1, 92, 100, new Entity("./enemies/Naga.gif")));
	AddAnimation("Hurt", new Animation(2, 92, 100, new Entity("./enemies/Naga_Hurt.gif")));
};

NightMare::NightMare()
{
	name = "Nightmare";
	maxHealthPoints = healthPoints = 35;
	maxMagicPoints = magicPoints = 10;
	imageWidth = 92;
	imageHeight = 96;

	abilities.push_back(new EnemyAttack());

	AddAnimation("Idle", new Animation(1, 92, 100, new Entity("./enemies/Nitemare.gif")));
	AddAnimation("Hurt", new Animation(2, 92, 100, new Entity("./enemies/Nitemare_Hurt.gif")));
};