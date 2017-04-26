#include "Roam.h"

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

void Roam::Enter(Bot* pBot)
{

}

void Roam::Execute(Bot* pBot)
{

}

void Roam::Exit(Bot* pBot)
{

}
