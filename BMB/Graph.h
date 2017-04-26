#pragma once
#include "Node.h"
#include "Shapes.h"
#include "Renderer.h"
#include "staticmap.h"
#include "Edge.h"
#include "rules.h"
#include <vector>
#include <list>


class Graph
{
private:
	//NodeVector stores a vector of nodes
	std::vector <Node> NodeVector;
	//AddNode adds a node at the specified location
	void AddNode(Vector2D location);
	//AddEdge adds an edge between two nodes taking into account the cost
	void AddEdge(Node* from, Node* to, float cost);
	
	//Node pointer of the current pointer
	Node* CurrentPtr;
	//Node pointer of the next pointer
	Node* NextPtr;

	//list of nodes that is the open set
	std::list<Node*> openSet;
	//list of nodes that is the closed set
	std::list<Node*> closedSet;


	//double for the cost
	double cost;

public:
	//constructor
	Graph();
	//destructor
	~Graph();
	//ResetAStar resets the pathfinding variables
	void resetAStar();

	//AnalyseMap places a rectangle on the map and then calls partition
	void AnalyseMap();
	//PartitionMap divides the map up into smaller squares
	void PartitonMap(Rectangle2D rectangle);
	//FillEdgeList fills the edge lists
	void FillEdgeList();
	//Draw displays the pathfinding system on the screen
	void Draw();

	//Pathfind is called outside of the class and is given two locations
	std::vector<Vector2D> Pathfind(Vector2D from, Vector2D to);
	//calculatePath is called by Pathfind() and is given two nodes
	std::vector<Vector2D> calculatePath(Node* start, Node* goal);
	//getPath adds the node in the path to the vector and returns the
	//path
	std::vector<Vector2D> getPath(Node* current);
	//findClosestVisibleNode finds the closest node to the location
	//given in Pathfind()
	Node* findClosestVisibleNode(Vector2D pos);
	//getHeuristic calculates and returns the heurisitc between nodes
	float getHeuristic(Node* from, Node* to);
	//getLowestFScore calculates and returns the lowest F score
	Node* getLowestFScore();

	//instance of the class that is used in the Bot class
	static Graph instance;
};

