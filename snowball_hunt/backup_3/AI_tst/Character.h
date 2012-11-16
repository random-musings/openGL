#pragma once

enum npcState {HIDE, PREPARE,HUNT, ATTACK, WAITING};

class Character:Obstacle
{
	bool isAlive;
	int strikeRange;
	int damage;
	int maxDamage;
	enum npcState currState;

	bool inDanger;

public:
	Character(void);
	~Character(void);
};
