#include "Ai.h"
#include <iostream>
#include <queue>
bool Ai::BFS(Node* startNode, Node* endNode)
{
	bfsPath.clear();
	bfsVisited.clear();
	bfsColor = Color{ 0,200,0,100};
	for (auto& gridRow : grid1) {
		for (auto& node : gridRow) {
			node.Laundry();
		}
	}
	std::queue<Node*> openSet;
	openSet.push(startNode);
	startNode->visited = true;
	while (!openSet.empty()) {
		Node* currentNode = openSet.front();
		openSet.pop();
		bfsVisited.push_back(currentNode);
		if (currentNode == endNode) {
			while (currentNode != startNode) {
				bfsPath.push_back(currentNode);
				currentNode = currentNode->parent;
			}
			std::cout << "A path was found" << std::endl;
			return true;
		}
		for (Node* neighbour : GetNeighbours(currentNode, grid1)) {
			if (neighbour->blocked || neighbour->visited) continue;
			neighbour->step = currentNode->step + 1;
			neighbour->parent = currentNode;
			neighbour->visited = true;

			openSet.push(neighbour);

		}
	}
	std::cout << "No path was found" << std::endl;
	return false;

}