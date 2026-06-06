#include "Ai.h"
#include <iostream>
#include <stack>
bool Ai::DFS(Node* startNode, Node* endNode) {

	dfsPath.clear();
	dfsVisited.clear();
	dfsColor = Color{ 200,0,0,100};
	for (auto& gridRow : grid2) {
		for (auto& node : gridRow) {
			node.Laundry();
		}
	}
	std::stack<Node*> openSet;
	openSet.push(startNode);
	startNode->visited = true;
	while (!openSet.empty()) {
		Node* currentNode = openSet.top();
		openSet.pop();
		dfsVisited.push_back(currentNode);
		if (currentNode == endNode) {
			while (currentNode != startNode) {
				dfsPath.push_back(currentNode);
				currentNode = currentNode->parent;
			}
			std::cout << "A path was found" << std::endl;
			return true;
		}
		for (Node* neighbour : GetNeighbours(currentNode,grid2)) {
			if (neighbour->blocked || neighbour->visited) continue;
			neighbour->step = currentNode->step + 1;
			neighbour->parent = currentNode;
			neighbour->visited = true;
			if (neighbour == endNode)
			{
				dfsVisited.push_back(neighbour);
				Node* parent = neighbour;
				while (parent != startNode)
				{
					dfsPath.push_back(parent);
					parent = parent->parent;
				}

				std::cout << "A path was found\n";
				return true;
			}
			openSet.push(neighbour);
		}
	}
	std::cout << "No path was found" << std::endl;
	return false;
}