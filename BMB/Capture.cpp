#include "Attack.h"
#include "Capture.h"
#include "FindResupplyPoint.h"
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
	//Set behaviours
	pBot->behaviourInstance.SetBehaviours(true, false, false, false, false, false, true);

}

void Capture::Execute(Bot* pBot)
{
	//Update the bot's speed
	pBot->SetBotAcceleration(pBot->behaviourInstance.AccumulateBehaviours(pBot->GetEnemyBotLocation(), pBot->GetEnemyBotVelocity(),
		pBot->GetLocation(), pBot->GetVelocity(), pBot->GetPath()));

	//Check the enemy is within part of a radius of the domination point
	if (pBot->CalculateDistanceToEnemyBot() < (DOMINATIONRANGE * 10))
	{
		//If the enemy bot is alive and within the range, attack them
		if (DynamicObjects::GetInstance()->GetBot(1, pBot->GetClosestEnemyBot()).IsAlive() && pBot->GetLineOfSight(pBot->GetClosestEnemyBot()))
		{
			pBot->ChangeState(Attack::GetInstance());
		}
	}

	//If the bot's team has 2 or more domination points captured, switch to the defend 
	//state
	else if (pBot->GetNumberOfCapturedDPs() >= 2)
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

