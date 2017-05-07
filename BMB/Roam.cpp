//State description: the default state in which the bot checks for the closest enemy and
//domination point, evaluates its health and ammo and generates the path to whichever,
//changing to Attack, Capture or FindResupplyPoint

#include "Roam.h"
#include "FindResupplyPoint.h"
#include "GoToDominationPoint.h"
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
	//pBot->SetPath(Graph::instance.Pathfind(pBot->GetLocation(), pBot->GetBotStartingDominationPoint()));

	pBot->behaviourInstance.SetBehaviours(false, false, false, false, false, false, false);
}

//Called on every frame of the state
void Roam::Execute(Bot* pBot)
{
	//If the bot is alive
	if (pBot->IsAlive())
	{
		if (pBot->GetAmmo() == 0)
		{
			pBot->ChangeState(FindResupplyPoint::GetInstance());
		}

		else
		{
			pBot->ChangeState(GoToDominationPoint::GetInstance());
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
	pBot->behaviourInstance.SetBehaviours(false, false, false, false, false, false, false);
}

void Roam::Release()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

wchar_t* Roam::GetStateName()
{
	return L"Roam";
}

