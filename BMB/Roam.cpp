//State description: the default state in which the bot checks for the closest enemy and
//domination point, evaluates its health and ammo and generates the path to whichever,
//changing to Attack, Capture or FindResupplyPoint

//State includes
#include "Roam.h"
#include "Attack.h"
#include "Capture.h"
#include "Guard.h"
#include "FindResupplyPoint.h"
#include "Start.h"

//Other includes
#include "Graph.h"
#include "dynamicObjects.h"
#include "staticmap.h"

//Initialise the instance of the state to null
Roam* Roam::instance = nullptr;

Roam::Roam()
{
}


Roam::~Roam()
{
}

Roam* Roam::GetInstance()
{
	if (!instance)
	{
		instance = new Roam();
	}

	return instance;
}

//Called on entry of the state
void Roam::Enter(Bot* pBot)
{
	pBot->SetBehaviours(true, false, false, false, false, true, true);
	//pBot->GetBehaviourInstance.FollowPath()
	pBot->GetClosestEnemyBot();
}

//Called on every frame of the state
void Roam::Execute(Bot* pBot)
{
	//Update velocities


	//If the bot is alive
	if (pBot->IsAlive())
	{
		//If the bot has no ammo, change to the state
		if (pBot->GetAmmo() <= 0)
		{
			pBot->ChangeState(FindResupplyPoint::GetInstance());
		}

		//Else if the closest enemy bot is within line of sight and has an accuracy of 70%+
		else if ((pBot->GetLineOfSight(pBot->GetEnemyBotID())) && (pBot->GetAccuracy() >= 0.7))
		{
			pBot->ChangeState(Attack::GetInstance());
		}

		//Else if there are less than 2 domination points captured
		else if (pBot->GetNumberOfCapturedDPs() < 2)
		{
			pBot->ChangeState(Capture::GetInstance());
		}

		//Else if there are more than 2 domination points captured
		else if (pBot->GetNumberOfCapturedDPs() > 2)
		{
			pBot->ChangeState(Guard::GetInstance());
		}
	}

	else
	{
		pBot->ChangeState(Start::GetInstance());
	}
	
}

//Called on exit of the state
void Roam::Exit(Bot* pBot)
{
	pBot->SetBehaviours(false, false, false, false, false, false, false);
}

