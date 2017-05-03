#include "Start.h"
#include "Roam.h"

//Initialise the instance of the state to null
Start* Start::instance = nullptr;

Start::Start()
{
}


Start::~Start()
{
}

Start* Start::GetInstance()
{
	if (!instance)
	{
		instance = new Start();
	}

	return instance;
}

void Start::Enter(Bot* pBot)
{
	pBot->SetBehaviours(true, false, false, false, false, true, true);
}

void Start::Execute(Bot* pBot)
{
	pBot->ChangeState(Roam::GetInstance());
}

void Start::Exit(Bot* pBot)
{

}