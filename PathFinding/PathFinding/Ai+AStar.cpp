#include "Ai.h"
#include <iostream>
#include <queue>
void Ai::AStar(Node* startNode, Node* endNode){
	aStarPath.clear();
	aStarVisited.clear();
	aStarColor = Color{ 150,150,150,100 };
	for (auto& gridRow : grid2) {
		for (auto& node : gridRow) {
			node.Laundry();
		}
	}
	auto Heuristic = [](Node* a, Node* b)
		{
			return abs(a->col - b->col) + abs(a->row - b->row);
		};

	auto CompareStar = [](Node* a, Node* b)
		{
			if (a->fCost == b->fCost)
				return a->hCost > b->hCost;
			return a->fCost > b->fCost;
		};
	std::priority_queue <Node*, std:: vector<Node*>, decltype(CompareStar) > openSet(CompareStar);
	startNode->gCost = 0;
	startNode->hCost = Heuristic(startNode, endNode);
	startNode->fCost = startNode->gCost + startNode->hCost;
	startNode->visited = true;
	openSet.push(startNode);
	while (!openSet.empty()) {
		Node* currentNode = openSet.top();
		openSet.pop();
		aStarVisited.push_back(currentNode);
		if (currentNode == endNode) {
			while (currentNode != startNode) {
				aStarPath.push_back(currentNode);
				currentNode = currentNode->parent;
			}
			std::cout << "A path was found" << std::endl;
			return;
		}
		for (auto neighbour : GetNeighbours(currentNode, grid2)) {
			if (neighbour->blocked || neighbour->visited) continue;
			float tentativeCost = currentNode->gCost + currentNode->weight;
			if (tentativeCost < neighbour->gCost) {
				neighbour->gCost = tentativeCost;
				neighbour->hCost = Heuristic(neighbour, endNode);
				neighbour->fCost = neighbour->gCost + neighbour->hCost;
				neighbour->step = currentNode->step + currentNode->weight;
				neighbour->parent = currentNode;
				neighbour->visited = true;
				openSet.push(neighbour);
			}
		}
	}

}