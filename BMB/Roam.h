#include "bot.h"

#pragma once


class Roam : public State<Bot>
{
private:
	Roam();
	~Roam();

	//Class instance
	static Roam* instance;

	//Decision bools
	bool attackTheEnemy;
	bool captureDominationPoint;
	bool findResupplyPoint;

	//Vectors of enemy and domination point positions
	float enemyBotDistance;
	Vector2D DPDistance;

	//Member functions
	void SetBotTarget(Bot* pBot);

public:
	static Roam* GetInstance();
	void Enter(Bot* pBot);
	void Execute(Bot* pBot);
	void Exit(Bot* pBot);
};

