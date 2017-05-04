#include "FindResupplyPoint.h"
#include "Roam.h"


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
	//Set behaviours
	pBot->SetBehaviours(false, false, false, false, false, true, true);

	//Set path to closest resupply point
	pBot->GeneratePath(pBot->GetLocation(), pBot->GetClosestResupplyPoint());
}

void FindResupplyPoint::Execute(Bot* pBot)
{
	//If the resupply is in line of sight
	if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), pBot->GetClosestResupplyPoint()));
	{
		//Seek to it and capture
		pBot->SetBehaviours(true, false, false, false, false, false, true);
	}

	//Update the bot's speed
	pBot->SetBotAcceleration(pBot->AccumulateBehaviours(pBot->GetEnemyBotLocation(), pBot->GetEnemyBotVelocity(),
		pBot->GetLocation(), pBot->GetVelocity(), pBot->GetPathInstance()));

	//Get the closest enemy bot again
	pBot->GetClosestEnemyBot();

	//Check the enemy is within part of a radius of the resupply point
	if (pBot->GetDistanceToEnemyBot() < (DOMINATIONRANGE * 6))
	{
		//If the enemy bot is alive and within the range, flee from it
		if (DynamicObjects::GetInstance()->GetBot(1, pBot->GetEnemyBotID()).IsAlive())
		{
			pBot->SetBehaviours(false, false, false, false, true, true, true);
		}
	}

	//If the bot has full ammo, go back to roaming
	if (pBot->GetAmmo() == MAXAMMO)
	{
		pBot->ChangeState(Roam::GetInstance());
	}

	//Else, go back to roaming
	else
	{
		pBot->ChangeState(Roam::GetInstance());
	}
		
}

void FindResupplyPoint::Exit(Bot* pBot)
{
	pBot->SetBehaviours(false, false, false, false, false, false, false);
}
