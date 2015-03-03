#include "FullPartyMembers.h"

Fighter::Fighter()
{
	maxHealthPoints = healthPoints = 50;
	maxMagicPoints = magicPoints = 0;
	weaponEquipped = "Sword";
	
	weapons.push_back(new Sword(this));
	abilities.push_back(new Attack(this));
	abilities.push_back(new SkipTurn(this));

	AddAnimation("Idle", new Animation(1, 36, 100, new Entity("./fighter/Fighter.png")));
	AddAnimation("Walk", new Animation(2, 36, 100, new Entity("./fighter/Fighter_Walk.png")));
	AddAnimation("Attack", new Animation(2, 36, 100, new Entity("./fighter/Fighter_Attack.png")));
	AddAnimation("Hurt", new Animation(2, 36, 100, new Entity("./fighter/Fighter_Hurt.png")));
	AddAnimation("Dodge", new Animation(5, 46, 100, new Entity("./fighter/Fighter_Dodge.png")));
	AddAnimation("Healed", new Animation(9, 36, 100, new Entity("./fighter/Fighter_Healed.png")));
	AddAnimation("Dieing", new Animation(3, 50, 100, new Entity("./fighter/Fighter_Dieing.png")));
	AddAnimation("Dead", new Animation(1, 50, 100, new Entity("./fighter/Fighter_Dead.gif")));
	AddAnimation("Sword", new Animation(4, 54, 100, new Entity("./fighter/sword.png")));
	AddAnimation("Lose", new Animation(1, 50, 100, new Entity("./fighter/Fighter_Dead_LOSE.gif")));
};

BlackMage::BlackMage()
{
	maxHealthPoints = healthPoints = 40;
	maxMagicPoints = magicPoints = 25;

	abilities.push_back(new Blizzaga(this));
	abilities.push_back(new Death(this));
	abilities.push_back(new SkipTurn(this));

	AddAnimation("Idle", new Animation(1, 36, 100, new Entity("./blackMage/BlackMage.gif")));
	AddAnimation("Blizzaga", new Animation(2, 66, 100, new Entity("./blackMage/BlackMage_Blizzaga.gif")));
	AddAnimation("Death", new Animation(2, 66, 100, new Entity("./blackMage/BlackMage_Death.gif")));
	AddAnimation("Hurt", new Animation(2, 36, 100, new Entity("./blackMage/BlackMage_Hurt.gif")));
	AddAnimation("Dodge", new Animation(5, 46, 100, new Entity("./blackMage/BlackMage_Dodge.gif")));
	AddAnimation("Healed", new Animation(9, 36, 100, new Entity("./blackMage/BlackMage_Healed.gif")));
	AddAnimation("Dieing", new Animation(3, 52, 100, new Entity("./blackMage/BlackMage_Dieing.gif")));
	AddAnimation("Dead", new Animation(1, 52, 100, new Entity("./blackMage/BlackMage_Dead.gif")));
	AddAnimation("Lose", new Animation(1, 50, 100, new Entity("./blackMage/BlackMage_Dead_LOSE.gif")));
};

WhiteMage::WhiteMage()
{
	maxHealthPoints = healthPoints = 30;
	maxMagicPoints = magicPoints = 20;

	abilities.push_back(new Heal(this));
	abilities.push_back(new Lamp(this));
	abilities.push_back(new SkipTurn(this));

	AddAnimation("Idle", new Animation(1, 36, 100, new Entity("./whiteMage/WhiteMage.gif")));
	AddAnimation("Heal", new Animation(2, 64, 100, new Entity("./whiteMage/WhiteMage_Heal.gif")));
	AddAnimation("Lamp", new Animation(2, 64, 100, new Entity("./whiteMage/WhiteMage_Lamp.gif")));
	AddAnimation("Hurt", new Animation(2, 36, 100, new Entity("./whiteMage/WhiteMage_Hurt.gif")));
	AddAnimation("Dodge", new Animation(5, 46, 100, new Entity("./whiteMage/WhiteMage_Dodge.gif")));
	AddAnimation("Healed", new Animation(9, 36, 100, new Entity("./whiteMage/WhiteMage_Healed.gif")));
	AddAnimation("Dieing", new Animation(3, 52, 100, new Entity("./whiteMage/WhiteMage_Dieing.gif")));
	AddAnimation("Dead", new Animation(1, 52, 100, new Entity("./whiteMage/WhiteMage_Dead.gif")));
	AddAnimation("Lose", new Animation(1, 50, 100, new Entity("./whiteMage/WhiteMage_Dead_LOSE.gif")));
};

RedMage::RedMage()
{
	maxHealthPoints = healthPoints = 40;
	maxMagicPoints = magicPoints = 50;

	abilities.push_back(new SacredFire(this));
	abilities.push_back(new Fog(this));
	abilities.push_back(new SkipTurn(this));

	AddAnimation("Idle", new Animation(1, 36, 100, new Entity("./redMage/RedMage.gif")));
	AddAnimation("Sacred Fire", new Animation(2, 66, 100, new Entity("./redMage/RedMage_SacredFire.gif")));
	AddAnimation("Fog", new Animation(2, 54, 100, new Entity("./redMage/RedMage_Fog.gif")));
	AddAnimation("Hurt", new Animation(2, 36, 100, new Entity("./redMage/RedMage_Hurt.gif")));
	AddAnimation("Dodge", new Animation(5, 46, 100, new Entity("./redMage/RedMage_Dodge.gif")));
	AddAnimation("Healed", new Animation(9, 36, 100, new Entity("./redMage/RedMage_Healed.gif")));
	AddAnimation("Dieing", new Animation(3, 52, 100, new Entity("./redMage/RedMage_Dieing.gif")));
	AddAnimation("Dead", new Animation(1, 52, 100, new Entity("./redMage/RedMage_Dead.gif")));
	AddAnimation("Lose", new Animation(1, 50, 100, new Entity("./redMage/RedMage_Dead_LOSE.gif")));
};