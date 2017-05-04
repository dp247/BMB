//State description: the default state in which the bot checks for the closest enemy and
//domination point, evaluates its health and ammo and generates the path to whichever,
//changing to Attack, Capture or FindResupplyPoint

#include "Roam.h"
#include "Capture.h"
#include "FindResupplyPoint.h"
#include "Guard.h"
#include "Start.h"


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
	//pBot->GetBehaviourInstance.FollowPath() -- pathfinding?

	//Get the closest enemy bot (even if not in LOS) and set the appropriate variable
	pBot->GetClosestEnemyBot();
}

//Called on every frame of the state
void Roam::Execute(Bot* pBot)
{
	//Update velocities
	//how?

	//If the bot is alive
	if (pBot->IsAlive())
	{
		//If the bot has no ammo, change to the state
		if (pBot->GetAmmo() <= 0)
		{
			pBot->ChangeState(FindResupplyPoint::GetInstance());
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

	//If the bot is dead, change to the reset state
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

