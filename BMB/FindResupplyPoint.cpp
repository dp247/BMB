#include "FindResupplyPoint.h"

//Initialise the instance of the state to null
FindResupplyPoint* FindResupplyPoint::instance = nullptr;

FindResupplyPoint::FindResupplyPoint()
{
}


FindResupplyPoint::~FindResupplyPoint()
{
}

FindResupplyPoint* FindResupplyPoint::GetInstance()
{
	if (!instance)
	{
		instance = new FindResupplyPoint();
	}

	return instance;
}

void FindResupplyPoint::Enter(Bot* pBot)
{
	//Find nearest resupply point -- need new function
	//Set behaviours
	//Set path to point
}

void FindResupplyPoint::Execute(Bot* pBot)
{
	//If resupply point is in line of sight
		//Seek to it

	//If enemy is nearby - call GetClosestEnemy and check LineOfSight on the enemy ID
		//Flee away from enemy

	//If ammo is full
		//Change to Roam state
		
}

void FindResupplyPoint::Exit(Bot* pBot)
{

}

//Add in find nearest resupply function