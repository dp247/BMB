#pragma once
#include "shapes.h"
#include "Behaviours.h"

class Bot
{
protected:
	//Direction data
	Vector2D m_Position;			// Current world coordinates
	Vector2D m_Velocity;			// Current velocity
	Vector2D m_Acceleration;		// Current acceleration
	float m_dDirection;				// Direction the bot is pointing in. radians anticlockwise from south

	//Firing data
	bool m_bFiring;					// If true, bot is firing
	bool m_bAiming;					// If true, bot is aiming and cannot move
	int m_iAimingAtTeam;			// Team number of the bot being aimed at
	int m_iAimingAtBot;				// Number of the bot being aimed at
	int m_iAmmo;					// Number of ammo left
	float m_dAccuracy;				// Accuracy of the current firing solution (1 == 100%)

	//Closest object data
	int m_iClosestBot;				// ID of the closest enemy bot
	float m_dClosestBotDistance;	// Distance of the closest enemy bot
	Vector2D m_vClosestRP;			// Location of the closest resupply point
	int dominationPointToTarget;	// ID of domination point to target
	Vector2D m_vClosestDP;			// Location of the closest domination point

	//Timers
	float m_dTimeToCoolDown;		// Countdown until the time the bot can shoot again
	float m_dTimeToRespawn;			// Countdown until the bot can respawn. If zero or below, bot is alive

	//Bot data
	int m_iOwnTeamNumber;			// Bot's team number
	int m_iOwnBotNumber;			// Bot's own bot number
	int m_iHealth;					// Bot's health (100 max)
	State<Bot>* currentState;		// The current state
	State<Bot>* previousState;		// The previous state
	std::vector <Vector2D> m_Path;  // Vector of path locations

	Vector2D targetPoint;			//it complained when I took this out

public:
	Bot();	

	Behaviours behaviourInstance;	// Bot's behaviour instance


	//Flow functions --------------------------------------------------------------------
	// Runs once each frame. Handles physics, shooting, and calls
	// ProcessAI
	void Update(float frametime);

	// This is your function. Use it to set up any states at the beginning of the game
	// and analyse the map.
	// Remember that bots have not spawned yet, so will not be in their
	// starting positions.
	void StartAI();

	// This is your function. Use it to set the orders for the bot.
	// Will be called once each frame from Update
	void ProcessAI();

	// This is a quick n' dirty AI for team 2.
	// Try to make team 1 better than this.
	// Will be called once each frame from Update
	void ProcessAIBadly();

	//ChangeState changes the state
	void ChangeState(State<Bot>* newState);

	void ChangeToPreviousState();

	//Other functions -------------------------------------------------------------------
	// Reload the bot's weapon
	void Reload();

	// Restarts the bot in a new location, with full heath, etc
	void PlaceAt(Vector2D position);	
	
	// Returns true if the bot is currently not respawning
	bool IsAlive();					

	// Call this to set the bot to shoot, if it can.
	// Once a shot it taken, the bot will not shoot again unless told to do so.
	void Shoot();

	// Delivers the specified damage to the bot.
	// If this drops health below zero, the bot will die
	// and will respawn at the spawn point after a specified interval
	void TakeDamage(int amount);

	// Stops the bot from aiming, so it can move again
	void StopAiming();

	void DrawPath();

	//Calculation functions -------------------------------------------------------------
	
	// Returns the distance to the closest enemy (set in GetClosestEnemyBot())
	float CalculateDistanceToEnemyBot(Bot target);

	// Get the domination point that each bot will initially go to
	Vector2D GetBotStartingDominationPoints();

	// Get the current domination point target
	Vector2D GetCurrentBotDominationPoint();

	int GetDomNumber();
	
	// Calculates the closest enemy to the bot
	int GetClosestEnemyBot();
	
	// Calculates the closest non-owned domination point to the bot
	Vector2D GetClosestUnOwnedDominationPoint(int OwnTeamNumber);

	// Calculates the closest owned domination point to the bot
	Vector2D GetClosestOwnedDominationPoint(int OwnTeamNumber);

	// Calculates the closest resupply point to the bot
	Vector2D GetClosestResupplyPoint();

	// Returns the position of the enemy bot
	Vector2D GetEnemyBotLocation();

	// Returns the velocity of the enemy bot
	Vector2D GetEnemyBotVelocity();

	// Gets the line of sight for the enemy bot
	bool GetLineOfSight(int enemyBot);

	// Returns the number of captured domination points
	int GetNumberOfCapturedDPs();

	//Getter functions ------------------------------------------------------------------

	// Returns the current accuracy of the bot.
	// Accuracy is the probability of hitting the current target.
	// If the bot is not aiming, this will be zero.
	double GetAccuracy();

	// Returns the amount of ammo that the bot has
	int GetAmmo();

	// Returns the bot's own number
	int GetBotNumber();

	// Returns the bot's team number
	int GetBotTeam();

	// Returns the direction the bot is pointing. In radians anticlockwise from south
	float GetDirection();

	// Returns the distance to the enemy bot set in the calculation function
	float GetDistanceToEnemyBot();

	// Return the bot's domination point number that it will defend
	int GetBotDominationPointNumber();

	// Returns the current health of the bot
	int GetHealth();

	// Returns the location of the bot
	Vector2D GetLocation();

	// Returns the path
	std::vector<Vector2D> GetPath();

	// Returns the number of the bot being aimed at.
	// Returns a negative number if no bot is being aimed at.
	int GetTargetBot();

	// Returns the number of the team of the bot being aimed at.
	// Returns a negative number if no bot is being aimed at.
	int GetTargetTeam();

	// Returns the velocity of the bot
	Vector2D GetVelocity();


	//Setter functions ------------------------------------------------------------------

	// Sets the acceleration of the bot
	Vector2D SetBotAcceleration(Vector2D newAccelerationValue);
	
	// Sets the bots own team number and bot number.
	// No need to call this
	void SetOwnNumbers(int teamNo, int botNo);

	//Clears and sets the path
	void SetPath(std::vector<Vector2D> path);

	// Sets the target of the current bot.
	// This will reset the accuracy to zero if the target bot 
	// has changed.
	// It also sets the bot to aiming mode, which means it will stop
	// moving.
	// If you want the bot to stop aiming, just set mbAiming = false
	// or use the StopAiming method
	void SetTarget(int targetTeamNo, int targetBotNo);

	void SetTargetDP(Vector2D target);

	//Set the velocity of the bot
	void SetVelocity(Vector2D newVelocity);
};