#include "bot.h"

#pragma once


class FindResupplyPoint : public State<Bot>
{
private:
	FindResupplyPoint();
	~FindResupplyPoint();

	static FindResupplyPoint* instance;

public:
	static FindResupplyPoint* GetInstance();
	void Enter(Bot* pBot);
	void Execute(Bot* pBot);
	void Exit(Bot* pBot);
	wchar_t* GetStateName();

	static void Release();
};