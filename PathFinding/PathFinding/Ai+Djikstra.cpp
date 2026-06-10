#include "Ai.h"
#include <queue>
#include <iostream>
void Ai::Djikstra(Node* startNode, Node* endNode) {
	djikstraPath.clear();
	djikstraVisited.clear();
	djikstraColor = Color{0,200,200,100};
	for (auto& gridRow : grid1) {
		for (auto& node : gridRow) {
			node.Laundry();
		}
	}
	auto Compare = [](Node* a, Node* b) {
		return a->gCost > b->gCost;
		};
	std::priority_queue<Node*, std::vector<Node*>, decltype(Compare)> openSet;
	startNode->gCost = 0;
	startNode->visited = true;
	openSet.push(startNode);
	while (!openSet.empty()) {
		Node* currentNode = openSet.top();
		openSet.pop();
		djikstraVisited.push_back(currentNode);
		if (currentNode == endNode) {
			while (currentNode != startNode) {
				djikstraPath.push_back(currentNode);
				currentNode = currentNode->parent;
			}
			std::cout << "A path was found" << std::endl;
			return;
		}
		for (auto neighbour : GetNeighbours(currentNode, grid1)) {
			if (neighbour->blocked || neighbour->visited) continue;
			float tentativeCost = currentNode->gCost + currentNode->weight;
			if (tentativeCost < neighbour->gCost) {
				neighbour->gCost = tentativeCost;
				neighbour->step = currentNode->step + currentNode->weight;
				neighbour->parent = currentNode;
				neighbour->visited = true;
				openSet.push(neighbour);
			}
		}
	}


}