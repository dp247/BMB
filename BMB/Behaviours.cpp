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
void Behaviours::SetBehaviours(bool Seek, bool Flee, bool Arrive, bool Pursue, bool Evade, bool Pathfind, bool AvoidWall)
{
	isSeeking = Seek;
	isFleeing = Flee;
	isArriving = Arrive;
	isPursuing = Pursue;
	isEvading = Evade;
	isPathfinding = Pathfind;
	isAvoidingWall = AvoidWall;
}

//Set the path
void Behaviours::SetPathInstance(std::vector<Vector2D>* path)
{
	m_Path = *path;
}

//Return the bot's current path
std::vector<Vector2D>* Behaviours::GetPathInstance()
{
	return &m_Path;
}

//Returns a Vector2D that sets a desired velocity to move to a target
Vector2D Behaviours::Seek(Vector2D targetPos, Vector2D botPos, Vector2D velocity)
{
  targetPosition.set(targetPos);
  botPosition.set(botPos);
  botVelocity.set(velocity);

  Vector2D desiredVelocity = (targetPosition - botPosition).unitVector() * MAXIMUMSPEED;

  return (desiredVelocity - botVelocity).unitVector() * MAXIMUMACCELERATION;
}

//Returns a Vector2D that sets a desired velocity to move away from a target
Vector2D Behaviours::Flee(Vector2D targetPos, Vector2D botPos, Vector2D velocity)
{
  targetPosition.set(targetPos);
  botPosition.set(botPos);
  botVelocity.set(velocity);

  Vector2D desiredVelocity = (botPosition - targetPosition).unitVector() * MAXIMUMSPEED;

  Vector2D behaviourAccn = desiredVelocity - botVelocity;

	return behaviourAccn;
}

//Returns a Vector2D velocity that slows down as the bot approaches the destination
Vector2D Behaviours::Arrive(Vector2D targetPos, Vector2D botPos, Vector2D velocity)
{
  targetPosition.set(targetPos);
  botPosition.set(botPos);
  botVelocity.set(velocity);

  float distance = (targetPosition - botPosition).magnitude();

	float speed = distance / 5;

	if (speed > MAXIMUMSPEED)
	{
		speed = MAXIMUMSPEED;
	}

  Vector2D desiredVelocity = (targetPosition - botPosition).unitVector() * speed;

  Vector2D behaviourAccn = desiredVelocity - botVelocity;

	return behaviourAccn;
}

//Returns a Vector2D velocity used to pursue a moving target, working out the intercept using the
//target's position and velocity
Vector2D Behaviours::Pursue(Vector2D targetPos, Vector2D targetVelo, Vector2D botPos, Vector2D botVelo)
{
  targetPosition.set(targetPos);
  targetVelocity.set(targetVelo);
  botPosition.set(botPos);
  botVelocity.set(botVelo);

  double distance = (targetPosition - botPosition).magnitude();

	float time = distance / MAXIMUMSPEED;

  Vector2D target = targetPosition + targetVelocity * time;

  return Seek(target, botPosition, botVelocity);
}

//Not finished
Vector2D Behaviours::Evade(Vector2D targetPos, Vector2D botPos, Vector2D targetVelocity)
{
	double distance = (targetPos - botPos).magnitude();

	float time = distance / MAXIMUMSPEED;

	Vector2D target = targetPos + targetVelocity * time;

	return Flee(target, botPos, targetVelocity);
}


Vector2D Behaviours::FollowPath(Vector2D& botPos, Vector2D botVelocity)
{
	//Initialize a result variable
	Vector2D result;
	//Get the path size
	int pathSize = m_Path.size();

	if (pathSize > 0)
		result = Seek(m_Path[pathSize - 1], botPos, botVelocity);

	//If the path has more than one element
	if (m_Path.size() > 1)
	{
		//Set the result to seek the last element in path from the current 
		//bot position and using the current velocity


		//Check if the node after the last (i.e. the next node) can be seen
		if (StaticMap::GetInstance()->IsLineOfSight(botPos, m_Path[pathSize - 2]))
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
		return (100.0f * StaticMap::GetInstance()->GetNormalToSurface(circle));
	}

	return Vector2D(0, 0);
}

Vector2D Behaviours::AccumulateBehaviours(Vector2D targetPos, Vector2D targetVelocity, Vector2D botPos, Vector2D botVelocity, std::vector<Vector2D>* path)
{
	Vector2D acceleration;

	if (isSeeking)
		acceleration += Seek(targetPos, botPos, botVelocity);

	if (isFleeing)
		acceleration += Flee(targetPos, botPos, botVelocity);

	if (isArriving)
		acceleration += Arrive(targetPos, botPos, botVelocity);

	if (isPursuing)
		acceleration += Pursue(targetPos, targetVelocity, botPos,
		botVelocity);

	if (isEvading)
		acceleration += Evade(targetPos, botPos, targetVelocity);

	if (isPathfinding)
		acceleration += FollowPath(botPos, botVelocity);

	if (isAvoidingWall)
		acceleration += AvoidWall(botPos);

	return acceleration;
}

void Behaviours::GeneratePath(Vector2D from, Vector2D to)
{
	//Reverse the from and to points to make sense to humans
	m_Path = Graph::instance.Pathfind(to, from);

	//ErrorLogger::Writeln(L"Generating path");
}

void Behaviours::ClearPath()
{
	m_Path.clear();
}

void Behaviours::UpdateParameters(Vector2D botPos, Vector2D botVelo, Vector2D targetPos, Vector2D targetVelo)
{
  botPosition.set(botPos);
  botVelocity.set(botVelo);
  targetPosition.set(targetPos);
  targetVelocity.set(targetVelo);
}