#pragma once

#include "Edge.h"
#include "vector2D.h"
#include <vector>


struct Node
{
	std::vector<Edge> edgeList;	//list of edges
	Vector2D position;			//position of the node
	float g;					//the movement cost to move from the starting point A 
								//to a given square on the grid
	float f;					//variable to store movement cost + heuristic
	double score;				//score between a node
	int edgeCount;				//edge count
	Node* fromNode;


	void AddEdge(Node* from, Node* to, float cost);
};

