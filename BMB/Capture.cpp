#include "Capture.h"

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

}

void Capture::Execute(Bot* pBot)
{

}

void Capture::Exit(Bot* pBot)
{

}

