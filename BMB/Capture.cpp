#include "Attack.h"
#include "Capture.h"
#include "FindResupplyPoint.h"
#include "GoToDominationPoint.h"
#include "Guard.h"
#include "Roam.h"
#include "dynamicObjects.h"

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
	pBot->behaviourInstance.UpdateParameters(pBot->GetLocation(), pBot->GetVelocity(), DynamicObjects::GetInstance()->GetDominationPoint(2).m_Location, Vector2D(0, 0));

	//Set behaviours
	pBot->behaviourInstance.SetBehaviours(false, false, false, false, false, true, true);

}

void Capture::Execute(Bot* pBot)
{
	////Update the bot's speed
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

	//If the bot's target domination point is captured and the team owns 2 or more points, then switch to guard them
	if ((DynamicObjects::GetInstance()->GetDominationPoint(0).m_OwnerTeamNumber == PLAYERTEAM) && (pBot->GetNumberOfCapturedDPs() >= 2))
	{
		pBot->ChangeState(Guard::GetInstance());
	}

	//If the team has less than 2 (0 or 1) captured points, get the closest unowned point to the bot and go to it
	else
	{
		//pBot->SetTargetDP(pBot->GetClosestUnOwnedDominationPoint(PLAYERTEAM));
		//pBot->ChangeState(GoToDominationPoint::GetInstance());
	}




}

void Capture::Exit(Bot* pBot)
{
	pBot->behaviourInstance.SetBehaviours(false, false, false, false, false, false, false);
}

void Capture::Release()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

wchar_t* Capture::GetStateName()
{
	return L"Capture";
}

