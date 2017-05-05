#pragma once
#include "rules.h"
#include "vector2D.h"
#include "staticmap.h"
#include "Graph.h"
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
	bool isEvading;
	bool isPathfinding;
	bool isAvoidingWall;

	int enemy;						//ID of target enemy bot
	int dominationPoint;			//ID of target domination point
	Vector2D resupplyPoint;			//location of supply point

public:
	Behaviours();
	~Behaviours();

	Vector2D Seek(Vector2D targetPos, Vector2D botPos, Vector2D botVelocity);
	Vector2D Flee(Vector2D targetPos, Vector2D botPos, Vector2D botVelocity);
	Vector2D Arrive(Vector2D targetPos, Vector2D botPos, Vector2D botVelocity);
	Vector2D Pursue(Vector2D targetPos, Vector2D targetVelocity, Vector2D botPos, Vector2D botVelocity);
	Vector2D Evade(Vector2D targetPos, Vector2D botPos, Vector2D targetVelocity);
	Vector2D FollowPath(Vector2D& botPos, Vector2D botVelocity);
	Vector2D AvoidWall(Vector2D botPos);

	std::vector <Vector2D> m_Path;	//Vector of path locations
	State<Bot>* currentState;		//the current state
	State<Bot>* previousState;		//the previous state

	//Sets the behaviour variables
	void SetBehaviours(bool Seek, bool Flee, bool Arrive, bool Pursue, bool Evade, bool Pathfind, bool AvoidWall);

	//Sets the bots path
	void SetPathInstance(std::vector<Vector2D>* path);

	void ClearPath();

	//Gets the current path
	std::vector<Vector2D>* GetPathInstance();

	void GeneratePath(Vector2D from, Vector2D to);

	//Accumulate the velocities of all the behaviours
	Vector2D AccumulateBehaviours(Vector2D targetPos, Vector2D targetVelocity,
		Vector2D botPos, Vector2D botVelocity, std::vector<Vector2D>* path);
};

