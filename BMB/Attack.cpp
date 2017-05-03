#include "Attack.h"

//Initialise the instance of the state to null
Attack* Attack::instance = nullptr;

Attack::Attack()
{
}


Attack::~Attack()
{
}

Attack* Attack::GetInstance()
{
	if (!instance)
	{
		instance = new Attack();
	}

	return instance;
}

void Attack::Enter(Bot* pBot)
{
	//Set target 
}

void Attack::Execute(Bot* pBot)
{

}

void Attack::Exit(Bot* pBot)
{

}
