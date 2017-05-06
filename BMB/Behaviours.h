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
	bool isSeeking;        //switch to turn seek behaviour on/off
  bool isFleeing;        //switch to turn flee behaviour on/off
  bool isArriving;       //switch to turn arrive behaviour on/off
  bool isPursuing;       //switch to turn pursue behaviour on/off
  bool isEvading;        //switch to turn evade behaviour on/off
  bool isPathfinding;    //switch to turn pathfinding behaviour on/off
  bool isAvoidingWall;   //switch to turn wall avoidance behaviour on/off

public:
	Behaviours();
	~Behaviours();

  //Behaviours -----------------------------------------------------------------------------
	Vector2D Seek(Vector2D targetPos, Vector2D botPos, Vector2D botVelocity);
	Vector2D Flee(Vector2D targetPos, Vector2D botPos, Vector2D botVelocity);
	Vector2D Arrive(Vector2D targetPos, Vector2D botPos, Vector2D botVelocity);
	Vector2D Pursue(Vector2D targetPos, Vector2D targetVelo, Vector2D botPos, Vector2D botVelo);
	Vector2D Evade(Vector2D targetPos, Vector2D botPos, Vector2D targetVelocity);
	Vector2D FollowPath(Vector2D& botPos, Vector2D botVelocity);
	Vector2D AvoidWall(Vector2D botPos);

  Vector2D botPosition;
  Vector2D botVelocity;
  Vector2D targetPosition;
  Vector2D targetVelocity;

	std::vector <Vector2D> m_Path;	    //Vector of path locations
	State<Bot>* currentState;		        //the current state
	State<Bot>* previousState;		      //the previous state

  //Behaviour functions --------------------------------------------------------------------
  //Accumulate the velocities of all the behaviours
  Vector2D AccumulateBehaviours(Vector2D targetPos, Vector2D targetVelocity,
    Vector2D botPos, Vector2D botVelocity, std::vector<Vector2D>* path);

  //Sets the behaviour variables
  void SetBehaviours(bool Seek, bool Flee, bool Arrive, bool Pursue, bool Evade, bool Pathfind, bool AvoidWall);

  //Sets the bot/target positions and velocities that are used in the behaviours
  void UpdateParameters(Vector2D botPos, Vector2D botVelo, Vector2D targetPos, Vector2D targetVelo);

  //Path functions -------------------------------------------------------------------------
  //Clears the path instance
	void ClearPath();

  //Generates a path between two points
  void GeneratePath(Vector2D from, Vector2D to);

	//Gets the current path
	std::vector<Vector2D>* GetPathInstance();

  //Sets the bots path
  void SetPathInstance(std::vector<Vector2D>* path);

};

