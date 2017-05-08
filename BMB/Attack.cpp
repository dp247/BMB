#include "Attack.h"
#include "GoToDominationPoint.h"
#include "Roam.h"
#include "Start.h"
#include "FindResupplyPoint.h"

//Initialise the instance of the state to null
Attack* Attack::instance = nullptr;

Attack::Attack()
{
}


Attack::~Attack()
{
}

Attack* Attack::GetInstance()
{
	if (!instance)
	{
		instance = new Attack();
	}

	return instance;
}

void Attack::Enter(Bot* pBot)
{
  //If aiming, stop it
  pBot->StopAiming();

  //Aim at the closest enemy
  //pBot->SetTarget(1, pBot->GetClosestEnemyBot());

  //Update parameters
  pBot->behaviourInstance.UpdateParameters(pBot->GetLocation(), pBot->GetVelocity(), pBot->GetEnemyBotLocation(), pBot->GetEnemyBotVelocity());

  //Set behaviours
  pBot->behaviourInstance.SetBehaviours(false, false, false, true, false, false, true);
}

void Attack::Execute(Bot* pBot)
{
	//Should check if I'm alive	- if (go back to start if dead)
	if (pBot->IsAlive())
	{
		//If the bot does not have a target, go back to the domination point
		if (pBot->GetTargetBot() < 0)
		{
			pBot->ChangeState(GoToDominationPoint::GetInstance());
		}

		//If there is no ammo, go find some
		if (pBot->GetAmmo() < 1)
		{
			pBot->ChangeState(FindResupplyPoint::GetInstance());
		}

		//Set the target bot
		Bot enemy = DynamicObjects::GetInstance()->GetBot(1, pBot->GetTargetBot());

		//If the target is alive and in range
		if ((enemy.IsAlive()) && (pBot->CalculateDistanceToEnemyBot(enemy) < DISTANCETOENEMY))
		{
			//If accuracy is over 50%
			if (pBot->GetAccuracy() > 0.5)
			{
				pBot->Shoot();
			}
		}

		else
		{
			//Get a new enemy bot
			enemy = DynamicObjects::GetInstance()->GetBot(1, pBot->GetClosestEnemyBot());

			if (pBot->GetLineOfSight(enemy.GetBotNumber()) && (pBot->CalculateDistanceToEnemyBot(enemy) < DISTANCETOENEMY))
			{
				pBot->ChangeState(Attack::GetInstance());
			}

			else
			{
				pBot->ChangeState(GoToDominationPoint::GetInstance());
			}

		}
	}

	else
	{
		pBot->ChangeState(Start::GetInstance());
	}

}

void Attack::Exit(Bot* pBot)
{
	pBot->StopAiming();
	pBot->behaviourInstance.SetBehaviours(false, false, false, false, false, false, false);
}

void Attack::Release()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

wchar_t* Attack::GetStateName()
{
	return L"Attack";
}
