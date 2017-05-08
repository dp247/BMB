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
	//Set the bot's domination point to guard and set a path to it
	pBot->SetDominationPoint();
	pBot->SetPath(&Pathfind::GetInstance()->GeneratePath(pBot->GetLocation(), DynamicObjects::GetInstance()->GetDominationPoint(pBot->dominationPointToTarget).m_Location));

	//Set behaviours
	pBot->behaviourInstance.SetBehaviours(false, false, false, false, false, true, true);
}

void GoToDominationPoint::Execute(Bot* pBot)
{
	//Check if there is an enemy nearby
	if (pBot->CheckForEnemyBot())
	{
		pBot->ChangeState(Attack::GetInstance());
	}

	//If the domination point in the line of sight is not owned 
	if (DynamicObjects::GetInstance()->GetDominationPoint(pBot->dominationPointToTarget).m_OwnerTeamNumber != pBot->GetBotTeam())
	{
		if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), (DynamicObjects::GetInstance()->GetDominationPoint(pBot->dominationPointToTarget).m_Location)))
		{
			pBot->ChangeState(Capture::GetInstance());
		}
	}

	else
	{
		if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), (DynamicObjects::GetInstance()->GetDominationPoint(pBot->dominationPointToTarget).m_Location)))
		{
			pBot->ChangeState(Guard::GetInstance());
		}
	}

	//Update the bot's speed
	pBot->SetBotAcceleration(pBot->behaviourInstance.AccumulateBehaviours(pBot->GetEnemyBotLocation(), pBot->GetEnemyBotVelocity(),
		pBot->GetLocation(), pBot->GetVelocity(), *pBot->GetPath()));
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