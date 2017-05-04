#include "Attack.h"
#include "Capture.h"
#include "Guard.h"
#include "Roam.h"

#include "dynamicObjects.h"

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
	//Set behaviours
	pBot->SetBehaviours(false, false, false, false, false, true, true);

	//Generate path to the player owned domination point closest to the bot
	pBot->GeneratePath(pBot->GetLocation(), pBot->GetClosestDominationPoint(PLAYERTEAM));
}

void Guard::Execute(Bot* pBot)
{
	//If domination point is in line of sight
	if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), pBot->GetClosestDominationPoint(PLAYERTEAM)))
	{
		//Seek to it and capture
		pBot->SetBehaviours(true, false, false, false, false, true, true);
	}

	//Update the bot's speed
	pBot->SetBotAcceleration(pBot->AccumulateBehaviours(pBot->GetEnemyBotLocation(), pBot->GetEnemyBotVelocity(),
		pBot->GetLocation(), pBot->GetVelocity(), pBot->GetPathInstance()));

	//Get the closest enemy bot again
	pBot->GetClosestEnemyBot();

	//Check the enemy is within part of a radius of the domination point
	if (pBot->GetDistanceToEnemyBot() < (DOMINATIONRANGE * 6))
	{
		//If the enemy bot is alive and within the range, attack them
		if (DynamicObjects::GetInstance()->GetBot(1, pBot->GetEnemyBotID()).IsAlive())
		{
			pBot->ChangeState(Attack::GetInstance());
		}
	}

	//If the bot's team has 2 or more domination points captured, switch to the defend 
	//state
	else if (pBot->GetNumberOfCapturedDPs() < 2)
	{
		pBot->ChangeState(Capture::GetInstance());
	}

	//Else, go back to roaming around
	else
	{
		pBot->ChangeState(Roam::GetInstance());
	}
}

void Guard::Exit(Bot* pBot)
{
	pBot->SetBehaviours(false, false, false, false, false, false, false);
}

void Guard::Release()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
