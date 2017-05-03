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
	//Find closest domination point
		//Seek to it - set behaviours and path
}

void Guard::Execute(Bot* pBot)
{
	//If owned domination point is within LOS
		//Seek to it

	//If enemy is near
		//Change to attack state

	//If more than 2 domination points are taken
		//Change to roam state again
}

void Guard::Exit(Bot* pBot)
{
	//Reset behaviours
}
