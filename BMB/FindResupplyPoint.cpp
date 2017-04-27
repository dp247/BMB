#include "FindResupplyPoint.h"

//Initialise the instance of the state to null
FindResupplyPoint* FindResupplyPoint::instance = nullptr;

FindResupplyPoint::FindResupplyPoint()
{
}


FindResupplyPoint::~FindResupplyPoint()
{
}

FindResupplyPoint* FindResupplyPoint::GetInstance()
{
	if (!instance)
	{
		instance = new FindResupplyPoint();
	}

	return instance;
}

void FindResupplyPoint::Enter(Bot* pBot)
{

}

void FindResupplyPoint::Execute(Bot* pBot)
{

}

void FindResupplyPoint::Exit(Bot* pBot)
{

}