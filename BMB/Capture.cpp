#include "Attack.h"
#include "Capture.h"
#include "FindResupplyPoint.h"
#include "GoToDominationPoint.h"
#include "Guard.h"
#include "Roam.h"
#include "dynamicObjects.h"
#include "Pathfind.h"

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
	pBot->behaviourInstance.SetBehaviours(true, false, false, false, false, false, true);
}

void Capture::Execute(Bot* pBot)
{
	pBot->SetBotAcceleration(pBot->behaviourInstance.AccumulateBehaviours(pBot->GetEnemyBotLocation(), pBot->GetEnemyBotVelocity(),
		pBot->GetLocation(), pBot->GetVelocity(), *pBot->GetPath()));

	//Check if there is an enemy nearby
	if (pBot->CheckForEnemyBot())
	{
		pBot->ChangeState(Attack::GetInstance());
	}

	//If the domination point is in line of sight, seek to it
	if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(),
		DynamicObjects::GetInstance()->GetDominationPoint(pBot->dominationPointToTarget).m_Location))
	{
		pBot->behaviourInstance.UpdateParameters(pBot->GetLocation(), pBot->GetVelocity(), DynamicObjects::GetInstance()->GetDominationPoint(pBot->dominationPointToTarget).m_Location, Vector2D (0,0));
	}

	//If the bot's target domination point is captured and the team owns 2 or more points, then switch to guard them
	if ((DynamicObjects::GetInstance()->GetDominationPoint(0).m_OwnerTeamNumber == PLAYERTEAM) && (pBot->GetNumberOfCapturedDPs() >= 2))
	{
		pBot->ChangeState(Guard::GetInstance());
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

