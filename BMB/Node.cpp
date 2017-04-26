#include "Node.h"

void Node::AddEdge(Node* from, Node* to, float cost)
{
	Edge newEdge;
	newEdge.fromNode = from;
	newEdge.toNode = to;
	newEdge.cost = cost;
	edgeList.push_back(newEdge);
}
