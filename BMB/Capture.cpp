#include "Capture.h"

//Initialise the instance of the state to null
Capture* Capture::instance = nullptr;

Capture::Capture()
{
}


Capture::~Capture()
{
}

Capture* Capture::GetInstance()
{
	if (!instance)
	{
		instance = new Capture();
	}

	return instance;
}

void Capture::Enter(Bot* pBot)
{
	//Set behaviour -- arrive?
	//Find nearest non-owned domination point
		//function in bot class
	//Generate path to DP
}

void Capture::Execute(Bot* pBot)
{
	//If domination point is in line of sight
		//Seek to it and capture

	//If enemy is nearby - call GetClosestEnemy and check LineOfSight on the enemy ID
		//Change to attack state

	//If captured DP > 2
		//Change to guard state
}

void Capture::Exit(Bot* pBot)
{
	//Reset behaviours
}

