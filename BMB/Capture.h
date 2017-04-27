#include "bot.h"

#pragma once


class Capture
{
private:
	Capture();
	~Capture();

	static Capture* instance;

public:
	static Capture* GetInstance();
	void Enter(Bot* pBot);
	void Execute(Bot* pBot);
	void Exit(Bot* pBot);
};

