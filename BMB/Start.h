#include "bot.h"

#pragma once


class Start : public State<Bot>
{
private:
	Start();
	~Start();

	static Start* instance;

public:
	static Start* GetInstance();
	void Enter(Bot* pBot);
	void Execute(Bot* pBot);
	void Exit(Bot* pBot);
};

