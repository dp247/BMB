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
	//Set behaviours - pursue and generate path to bot

			
}

void Attack::Execute(Bot* pBot)
{
	//update velocities

	//if health >= 65
		//aim weapon and fire

	//if health < 65
		//switch to flee

	//if enemy is dead
		//switch back to roam (tunbleweed) state (or back to previous state?)

	//if no ammo
		//switch to findRP state
}

void Attack::Exit(Bot* pBot)
{
	//reload?
	//reset behaviours
}
