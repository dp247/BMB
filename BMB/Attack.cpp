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
	//if (instance)
	//{
	//	delete instance;
	//}
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
	//Set behaviours - pursue and generate path to bot
	pBot->SetBehaviours(false, false, false, true, false, true, true);

	//If aiming, stop it
	pBot->StopAiming();

	//Aim at the closest enemy
	pBot->SetTarget(1, pBot->GetEnemyBotID());

	//Generate a path to the enemy
	pBot->GeneratePath(pBot->GetLocation(), pBot->GetEnemyBotLocation());		
}

void Attack::Execute(Bot* pBot)
{
	//If the closest enemy bot is in line of sight
	if (pBot->GetLineOfSight(pBot->GetEnemyBotID()))
	{	
		//Update the bot's speed
		pBot->SetBotAcceleration(pBot->AccumulateBehaviours(pBot->GetEnemyBotLocation(), pBot->GetEnemyBotVelocity(),
			pBot->GetLocation(), pBot->GetVelocity(), pBot->GetPathInstance()));

		//If the targetted bot is alive
		if (DynamicObjects::GetInstance()->GetBot(1, pBot->GetEnemyBotID()).IsAlive())
		{
			//If the bot's own health is 50 or more
			if (pBot->GetHealth() >= 50)
			{
				//If the distance to the enemy bot is < 300
				if (pBot->GetDistanceToEnemyBot() < 300)
				{
					//If the bot's accuracy is better than 70%
					if (pBot->GetAccuracy() >= 0.7)
					{
						//Shoot
						pBot->Shoot();
					}
				}
			}

			//If the bot's health is lower than 50, disregard range and accuracy and just shoot
			else
			{
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
	pBot->SetBehaviours(false, false, false, false, false, false, false);
}
