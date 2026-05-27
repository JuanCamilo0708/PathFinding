#pragma once
#pragma once
#include "Node.h"
#include "raylib.h"
#include <vector>
class Ai
{
public:
#define ROWS 20
#define COLS 40
#define NODE_SIZE 25
	static const int screenWidth = COLS * NODE_SIZE;
	static const int screenHeight = ROWS * NODE_SIZE;
	std::vector<std::vector<Node>> grid;
	Node* start, * end;
	int stepCount = 0;
	bool pathFound = false;
	Node* GetNotBlockedNode();
	void Main();
	void Start();
	void Update();
	void Draw();
	void Interaction();
	void Restart();
	void SetUpGame();
	void SetHotSpot();
	std::vector<Node*> GetNeighbours(Node* node);

	void BFS(Node* startNode, Node* endNode);
	void DFS(Node* startNode, Node* endNode);
	void Djikstre(Node* startNode, Node* endNode);
	void AStar(Node* startNode, Node* endNode);

	void RandomSearch(Node* startNode, Node* endNode);

private:

};
