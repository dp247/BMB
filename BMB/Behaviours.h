#pragma once
#include "rules.h"
#include "vector2D.h"
#include "staticmap.h"
#include "Node.h"
#include "State.h"

class Bot;

class Behaviours
{
private:
	bool isSeeking;
	bool isFleeing;
	bool isArriving;
	bool isPursuing;
	bool isPathfinding;
	bool isAvoidingWall;

	int enemy;						//ID of target enemy bot
	int dominationPoint;			//ID of target domination point
	Vector2D reSupplyPoint;			//location of supply point

public:
	Behaviours();
	~Behaviours();

	Vector2D Seek(Vector2D target, Vector2D position, Vector2D velocity);
	Vector2D Flee(Vector2D target, Vector2D position, Vector2D velocity);
	Vector2D Arrive(Vector2D target, Vector2D position, Vector2D velocity);
	Vector2D Pursue(Vector2D targetPos, Vector2D botPos, Vector2D targetVelocity);
	Vector2D Evade(Vector2D targetPos, Vector2D botPos, Vector2D targetVelocity);
	Vector2D FollowPath(Vector2D& position, Vector2D velocity);
	Vector2D AvoidWall(Vector2D botPos);

	std::vector <Vector2D> m_Path;	//Vector of path locations
	State<Bot>* currentState;		//the current state
	State<Bot>* previousState;		//the previous state

	//Sets the behaviour variables
	void SetBehaviours(bool Seek, bool Flee, bool Arrive, bool Pursue, bool Pathfind, bool AvoidWall);

	//Sets the bots path
	void SetPath(std::vector<Vector2D>* path);

	//Gets the current path
	std::vector<Vector2D>* GetPath();

	//Accumulate the velocities of all the behaviours
	Vector2D AccumulateBehaviours(Vector2D targetPos, Vector2D targetVelocity,
		Vector2D botPos, Vector2D botVelocity, std::vector<Vector2D>* path);
};

