#include "Graph.h"

//Declare a graph instance
Graph Graph::instance;

//Constructor
Graph::Graph()
{
}

//Destructor
Graph::~Graph()
{
}

//AnalyseMap 
void Graph::AnalyseMap()
{
	Rectangle2D outline;
	outline.PlaceAt(1600, -1600, -1600, 1600);

	PartitonMap(outline);
}

//Function that partitions the map into smaller squares, so nodes can be generated
void Graph::PartitonMap(Rectangle2D rectangle)
{
	//If the area of the rectangle is less than 11000, return
	if (rectangle.GetArea() < 11000)
	{
		return;
	}

	//If a block is inside the rectangle
	else if (StaticMap::GetInstance()->IsInsideBlock(rectangle))
	{
		//Create four new Rectangle2D objects
		Rectangle2D r1, r2, r3, r4;

		//Place the new rectangles to divide the big rectangle
		r3.PlaceAt(rectangle.GetBottomLeft(), rectangle.GetCentre());
		r2.PlaceAt(rectangle.GetCentre(), rectangle.GetTopRight());
		r1.PlaceAt(r3.GetTopLeft(), r2.GetTopLeft());
		r4.PlaceAt(r3.GetBottomRight(), r2.GetBottomRight());

		//Call the function again for each of the four rectangles
		PartitonMap(r1);
		PartitonMap(r2);
		PartitonMap(r3);
		PartitonMap(r4);
	}

	else
	{
		//If a block is not inside the rectangle, add a node
		AddNode(rectangle.GetCentre());
	}
}

//Function that adds nodes to the vector
void Graph::AddNode(Vector2D location)
{
	//Create a new node
	Node newNode;
	//Set the position of the node
	newNode.position = location;
	//Put the position in the vector
	NodeVector.push_back(newNode);
}

std::vector<Vector2D> Graph::Pathfind(Vector2D from, Vector2D to)
{
	//find closest node to one
	//find closest node to other
	//run pathfind
	//return answer

	Node* p_Start = nullptr;
	Node* p_End = nullptr;

	p_Start = findClosestVisibleNode(from);
	p_End = findClosestVisibleNode(to);

	return calculatePath(p_Start, p_End);
	
}

//Function that finds the closest visible node
Node* Graph::findClosestVisibleNode(Vector2D pos)
{
	Node* closest = nullptr;

	std::vector <Node>::iterator it = NodeVector.begin();
	for (; it != NodeVector.end(); it++)
	{
		if (StaticMap::GetInstance()->IsLineOfSight(pos, it->position))
		{
			if (closest == nullptr)
			{
				closest = &(*it);
			}

			else if ((pos - closest->position).magnitude() > (pos - it->position).magnitude())
			{
				closest = &(*it);
			}
		}
	}

	return closest;
}

//Function to draw each node onto the map
void Graph::Draw()
{
	//Set the iterator to begin at the start of the list
	std::vector <Node>::iterator it = NodeVector.begin();
	//Set another iterator
	std::vector <Edge>::iterator iu;

//	//For every node
//	for (; it != NodeVector.end(); it++)
//	{
//		//Draw a dot for the node
//		Renderer::GetInstance()->DrawDot(it->position, 4);
//
//		//For every node in the edgeList
//		//for (iu = it->edgeList.begin(); iu != it->edgeList.end(); ++iu)
//		//{
//		//	//Draw the line
//		//	Renderer::GetInstance()->DrawLine(iu->fromNode->position, iu->toNode->position, 3);
//		//}
//	}
}

//Function to fill the list of edges between the nodes
void Graph::FillEdgeList()
{
	//Definition of iterator it
	std::vector<Node>::iterator it = NodeVector.begin();
	//Set the edge count to zero.
	it->edgeCount = 0;

	//for every node
	for (it; it != NodeVector.end(); ++it)
	{
		//by every other node
		for (std::vector<Node>::iterator iu = NodeVector.begin(); iu != NodeVector.end(); ++iu)
		{
			//if the nodes are in the line of sight of each other
			if (StaticMap::GetInstance()->IsLineOfSight(it->position, iu->position))
			{
				//Calculate the cost
				cost = (iu->position - it->position).magnitude();

				//If the cost is over 2 and lower than 700
				if ((cost > 2) && (cost < 700))
				{
					//If there are less edges than the max
					if (it->edgeCount < MAXEDGES)
					{
						//Add the values of the nodes
						it->AddEdge(&*it, &*iu, cost);
						//Increment the edge counter
						it->edgeCount++;
					}
				}
			}
		}
	}
}

bool contains(std::list<Node*> theList, Node* theNode)
{
	//looping through every element in the list
	for (Node* n : theList)
	{
		if (n == theNode)
		{
			return true;
		}
	}

	return false;
}

std::vector<Vector2D> Graph::calculatePath(Node* start, Node* goal)
{
	resetAStar();

	//Add the starting node to the frontier list
	openSet.push_back(start);

	start->fromNode = nullptr;
	start->g = 0;
	start->f = start->g + getHeuristic(start, goal);

	//while the open set is not empty
	while (!openSet.size() == 0)
	{
		Node* current = nullptr;
		current = getLowestFScore();

		if (current == goal)
		{
			return getPath(current);
		}

		openSet.remove(current);
		closedSet.push_back(current);

		//for each neighbouring node
		for (int i = 0; i < current->edgeList.size(); ++i)
		{
			//if the current node's neighbour is not in the closed set
			if (!contains(closedSet, current->edgeList[i].toNode))
			{
				//work out the new G score
				double newGScore = current->g + current->edgeList[i].cost;

				//if the new G score is less than the neighbouring node's G score or the neighbouring node is
				//not open
				if (newGScore < current->edgeList[i].toNode->g || !contains(openSet ,current->edgeList[i].toNode))
				{
					//Set the neigbouring node's from node to be the current node
					current->edgeList[i].toNode->fromNode = current;
					//Set the neighbouring node's G score to be the new G score
					current->edgeList[i].toNode->g = newGScore;
					//Set the neighbouring node's F score to be the new heuristic
					current->edgeList[i].toNode->f = newGScore + getHeuristic(current->edgeList[i].toNode, goal);
					
					//If the neighbouring node is not in the open set, add it.
					if (!contains(openSet, current->edgeList[i].toNode))
					{
						openSet.push_back(current->edgeList[i].toNode);
					}
				}
			}
		}
	}
}

//Function that resets the pathfinding system
void Graph::resetAStar()
{
	std::vector<Node>::iterator it;

	for (it = NodeVector.begin(); it != NodeVector.end(); it++)
	{
		it->f = 0;
		it->g = 0;

		it->fromNode = nullptr;
	}
}

//Function that gets the heuristic between two nodes
float Graph::getHeuristic(Node* from, Node* to)
{
	//initialize float for result
	float result = 0;

	//define two floats
	float yDiff, xDiff;

	//calculate the Y difference - the Y of to minus the Y of from
	yDiff = to->position.YValue - from->position.YValue;
	xDiff = to->position.XValue - from->position.XValue;

	result = yDiff + xDiff;

	return result;
}

//Function gets the lowest F score
Node* Graph::getLowestFScore()
{
	std::vector<Node>::iterator it;

	Node* lowestScoreNode = nullptr;
	float value = 10000000.0f;

	for (it = NodeVector.begin(); it != NodeVector.end(); it++)
	{
		if ((it->f < value) && (contains(openSet, &*it)))
		{
			lowestScoreNode = &*it;
			value = lowestScoreNode->f;
		}
	}

	return lowestScoreNode;
}

//Function to get the path of the current node
std::vector<Vector2D> Graph::getPath(Node* current)
{
	if (current->fromNode == nullptr)
	{
		std::vector<Vector2D> path;
		path.push_back(current->position);
		return path;
	}

	else
	{
		std::vector<Vector2D> path = getPath(current->fromNode);
		path.push_back(current->position);
		return path;
	}
}