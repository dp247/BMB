#include "Attack.h"
#include "Capture.h"
#include "GoToDominationPoint.h"
#include "Roam.h"
#include "dynamicObjects.h"

//Initialise the instance of the state to null
GoToDominationPoint* GoToDominationPoint::instance = nullptr;

GoToDominationPoint::GoToDominationPoint()
{
}


GoToDominationPoint::~GoToDominationPoint()
{
}

GoToDominationPoint* GoToDominationPoint::GetInstance()
{
	if (!instance)
	{
		instance = new GoToDominationPoint();
	}

	return instance;
}

void GoToDominationPoint::Enter(Bot* pBot)
{
	//Set behaviours
	pBot->behaviourInstance.SetBehaviours(false, false, false, false, false, true, true);

	//Get the closest enemy bot again
	pBot->GetClosestEnemyBot();

	//Generate path to the enemy domination point closest to the bot
	pBot->SetPath(Graph::instance.Pathfind(pBot->GetLocation(), pBot->GetClosestUnOwnedDominationPoint(PLAYERTEAM)));
}

void GoToDominationPoint::Execute(Bot* pBot)
{
	//If domination point is in line of sight
	if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), pBot->GetClosestUnOwnedDominationPoint(PLAYERTEAM)))
	{
		//Change to capture state
		pBot->ChangeState(Capture::GetInstance());
	}

	//Check the enemy is within part of a radius of the domination point
	//else if (pBot->GetDistanceToEnemyBot() < (DOMINATIONRANGE * 6))
	//	{
	//		//If the enemy bot is alive and within the range, attack them
	//		if (DynamicObjects::GetInstance()->GetBot(1, pBot->GetEnemyBotID()).IsAlive())
	//		{
	//			pBot->ChangeState(Attack::GetInstance());
	//		}
	//	}

	//Update the bot's speed
	pBot->SetBotAcceleration(pBot->behaviourInstance.AccumulateBehaviours(pBot->GetEnemyBotLocation(), pBot->GetEnemyBotVelocity(),
		pBot->GetLocation(), pBot->GetVelocity(), pBot->GetPath()));
}

void GoToDominationPoint::Exit(Bot* pBot)
{
	pBot->behaviourInstance.SetBehaviours(false, false, false, false, false, false, false);
}

void GoToDominationPoint::Release()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

wchar_t* GoToDominationPoint::GetStateName()
{
	return L"GoToDominationPoint";
}