#include "Behaviours.h"


Behaviours::Behaviours()
{
	isSeeking = false;
	isFleeing = false;
	isArriving = false;
	isPursuing = false;
	isPathfinding = false;
	isAvoidingWall = false;

	currentState = nullptr;
	previousState = nullptr;
}


Behaviours::~Behaviours()
{

}

//Set the behaviour variables
void Behaviours::SetBehaviours(bool Seek, bool Flee, bool Arrive, bool Pursue, bool Pathfind, bool AvoidWall)
{
	isSeeking = Seek;
	isFleeing = Flee;
	isArriving = Arrive;
	isPursuing = Pursue;
	isPathfinding = Pathfind;
	isAvoidingWall = AvoidWall;
}

//Set the path
void Behaviours::SetPath(std::vector<Vector2D>* path)
{
	m_Path = *path;
}

//Return the bot's current path
std::vector<Vector2D>* Behaviours::GetPath()
{

	return &m_Path;

}

Vector2D Behaviours::Seek(Vector2D target, Vector2D position, Vector2D velocity)
{
	Vector2D desiredVelocity = (target - position).unitVector() * MAXIMUMSPEED;

	Vector2D behaviourAccn = desiredVelocity - velocity;

	return behaviourAccn;
}

Vector2D Behaviours::Flee(Vector2D target, Vector2D position, Vector2D velocity)
{
	Vector2D desiredVelocity = (position - target).unitVector() * MAXIMUMSPEED;

	Vector2D behaviourAccn = desiredVelocity - velocity;

	return behaviourAccn;
}

Vector2D Behaviours::Arrive(Vector2D target, Vector2D position, Vector2D velocity)
{
	float distance = (target - position).magnitude();

	float speed = distance / 5;

	if (speed > MAXIMUMSPEED)
	{
		speed = MAXIMUMSPEED;
	}

	Vector2D desiredVelocity = (target - position).unitVector() * speed;

	Vector2D behaviourAccn = desiredVelocity - velocity;

	return behaviourAccn;
}

Vector2D Behaviours::Pursue(Vector2D targetPos, Vector2D botPos, Vector2D targetVelocity)
{
	double distance = (targetPos - botPos).magnitude();

	float time = distance / MAXIMUMSPEED;

	Vector2D target = targetPos + targetVelocity * time;

	return Seek(target, botPos, targetVelocity);
}

Vector2D Behaviours::Evade(Vector2D targetPos, Vector2D botPos, Vector2D targetVelocity)
{
	double distance = (targetPos - botPos).magnitude();

	float time = distance / MAXIMUMSPEED;

	Vector2D target = targetPos + targetVelocity * time;

	return Flee(target, botPos, targetVelocity);
}


Vector2D Behaviours::FollowPath(Vector2D& position, Vector2D velocity)
{
	//Initialize a result variable
	Vector2D result;
	//Get the path size
	int pathSize = m_Path.size();

	//If the path has more than one element
	if (m_Path.size() > 1)
	{
		//Set the result to seek the last element in path from the current 
		//bot position and using the current velocity
		result = Seek(m_Path.back(), position, velocity);

		//Check if the node after the last (i.e. the next node) can be seen
		if (StaticMap::GetInstance()->IsLineOfSight(position, m_Path[pathSize - 2]))
		{
			//Remove the node from the path
			m_Path.pop_back();
		}
	}
	//Return the result
	return result;
}

Vector2D Behaviours::AvoidWall(Vector2D botPos)
{
	//Create a circle
	Circle2D circle;
	//Place the circle around the bot 
	circle.PlaceAt(botPos, 75.0f);

	//Ask the engine if the circle is inside the block
	if (StaticMap::GetInstance()->IsInsideBlock(circle))
	{
		//Get the normal
		return (3.0f * StaticMap::GetInstance()->GetNormalToSurface(circle));
	}
}
