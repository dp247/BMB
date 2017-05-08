#include "Attack.h"
#include "Capture.h"
#include "GoToDominationPoint.h"
#include "Guard.h"
#include "dynamicObjects.h"
#include "Pathfind.h"

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
	pBot->SetDominationPoint();

	pBot->SetPath(&Pathfind::GetInstance()->GeneratePath(pBot->GetLocation(), DynamicObjects::GetInstance()->GetDominationPoint(pBot->dominationPointToTarget).m_Location));

	//Set behaviours
	pBot->behaviourInstance.SetBehaviours(false, false, false, false, false, true, true);
}

void GoToDominationPoint::Execute(Bot* pBot)
{
	//Update the bot's speed
	pBot->SetBotAcceleration(pBot->behaviourInstance.AccumulateBehaviours(pBot->GetEnemyBotLocation(), pBot->GetEnemyBotVelocity(),
		pBot->GetLocation(), pBot->GetVelocity(), *pBot->GetPath()));

	//Declare an enemy bot
	Bot enemy;

	//Loop through the enemies
	for (int i = 0; i < NUMBOTSPERTEAM; ++i)
	{
		enemy = DynamicObjects::GetInstance()->GetBot(ENEMYTEAM, i);

		//If an enemy is alive, in line of sight of the bot and within range of the enemy, change to attack
		if ((enemy.IsAlive()) && (pBot->GetLineOfSight(enemy.GetBotNumber()) && (pBot->CalculateDistanceToEnemyBot(enemy) < DISTANCETOENEMY)))
		{
			pBot->ChangeState(Attack::GetInstance());
		}
	}

	if (DynamicObjects::GetInstance()->GetDominationPoint(pBot->GetBotDominationPointNumber()).m_OwnerTeamNumber != pBot->GetBotTeam())
	{
		if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), (DynamicObjects::GetInstance()->GetDominationPoint(0).m_Location)))
		{
			pBot->ChangeState(Capture::GetInstance());
		}
	}

	else
	{
		if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), (DynamicObjects::GetInstance()->GetDominationPoint(0).m_Location)))
		{
			pBot->ChangeState(Guard::GetInstance());
		}
	}
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