#include "bot.h"

#pragma once


class GoToDominationPoint : public State<Bot>
{
private:
	GoToDominationPoint();
	~GoToDominationPoint();

	static GoToDominationPoint* instance;

public:
	static GoToDominationPoint* GetInstance();
	void Enter(Bot* pBot);
	void Execute(Bot* pBot);
	void Exit(Bot* pBot);
	wchar_t* GetStateName();

	void Release();
};

