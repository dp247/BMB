
//Other includes
#include "bot.h"
#include "Graph.h"
#include "dynamicObjects.h"
#include "staticmap.h"

#pragma once


class Roam : public State<Bot>
{
private:
	Roam();
	~Roam();

	//Class instance
	static Roam* instance;


public:
	static Roam* GetInstance();
	void Enter(Bot* pBot);
	void Execute(Bot* pBot);
	void Exit(Bot* pBot);
};

