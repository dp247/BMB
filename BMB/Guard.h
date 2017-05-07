#include "bot.h"

#pragma once


class Guard : public State<Bot>
{
private:
	Guard();
	~Guard();

	static Guard* instance;

public:
	static Guard* GetInstance();
	void Enter(Bot* pBot);
	void Execute(Bot* pBot);
	void Exit(Bot* pBot);
	wchar_t* GetStateName();

	static void Release();
};

