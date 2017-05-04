#pragma once

template <class EntityType>

class State
{
public:

	//Enter runs on entry of the state; sets behaviours
	virtual void Enter(EntityType* entity) = 0;

	//Update runs each frame of the state; checking code
	virtual void Execute(EntityType* entity) = 0;

	//Exit runs once the state is done
	virtual void Exit(EntityType* entity) = 0;
};