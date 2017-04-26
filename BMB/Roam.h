#include "bot.h"

#pragma once


class Roam : public State<Bot>
{
private:
	Roam();
	~Roam();

	static Roam* instance;

public:
	static Roam* GetInstance();
	void Enter(Bot* pBot);
	void Execute(Bot* pBot);
	void Exit(Bot* pBot);
};

