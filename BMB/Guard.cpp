#include "Guard.h"

//Initialise the instance of the state to null
Guard* Guard::instance = nullptr;

Guard::Guard()
{
}


Guard::~Guard()
{
}

Guard* Guard::GetInstance()
{
	if (!instance)
	{
		instance = new Guard();
	}

	return instance;
}

void Guard::Enter(Bot* pBot)
{

}

void Guard::Execute(Bot* pBot)
{

}

void Guard::Exit(Bot* pBot)
{

}
