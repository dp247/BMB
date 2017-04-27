#include "bot.h"

#pragma once


class Attack : public State<Bot>
{
private:
	Attack();
	~Attack();

	static Attack* instance;

public:
	static Attack* GetInstance();
	void Enter(Bot* pBot);
	void Execute(Bot* pBot);
	void Exit(Bot* pBot);
};

