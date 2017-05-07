#include "Attack.h"
#include "Roam.h"
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

  //Get the closest enemy bot again
  pBot->GetClosestEnemyBot();

  //Aim at the closest enemy
  pBot->SetTarget(1, pBot->GetEnemyBotID());

  //Generate a path to the enemy
  //pBot->GeneratePath(pBot->GetLocation(), pBot->GetEnemyBotLocation());

  //Update parameters
  pBot->behaviourInstance.UpdateParameters(pBot->GetLocation(), pBot->GetVelocity(), pBot->GetEnemyBotLocation(), pBot->GetEnemyBotVelocity());

  //Set behaviours
  pBot->behaviourInstance.SetBehaviours(false, false, false, true, false, false, true);
}

void Attack::Execute(Bot* pBot)
{
	//If the closest enemy bot is in line of sight
	if (pBot->GetLineOfSight(pBot->GetEnemyBotID()))
	{
		//If the targetted bot is alive
		if (DynamicObjects::GetInstance()->GetBot(1, pBot->GetEnemyBotID()).IsAlive())
		{
				//If the distance to the enemy bot is > 450, get closer to it
				if (pBot->GetDistanceToEnemyBot() > 450)
				{
					pBot->SetBotAcceleration(pBot->behaviourInstance.AccumulateBehaviours(pBot->GetEnemyBotLocation(), pBot->GetEnemyBotVelocity(),
						pBot->GetLocation(), pBot->GetVelocity(), pBot->GetPath()));
				}

        //If the bot's accuracy is better than 70%
        else if (pBot->GetAccuracy() >= 0.7)
        {
          //Shoot
          pBot->Shoot();
        }
		}

		//If the targetted bot is dead, switch back to roaming
		else
		{
			pBot->ChangeState(Roam::GetInstance());
		}
	}

	//If the bot has no ammo, switch to find a resupply point
	else if (pBot->GetAmmo() < 1)
	{
		pBot->ChangeState(FindResupplyPoint::GetInstance());
	}

	//If the bot does not have a target/is not aiming, set the target and aim at it
	else if (pBot->GetTargetTeam() != 1)
	{
		pBot->SetTarget(1, pBot->GetEnemyBotID());
	}

	//If the bot has no line of sight, go back to roaming
	else
	{
		pBot->ChangeState(Roam::GetInstance());
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
