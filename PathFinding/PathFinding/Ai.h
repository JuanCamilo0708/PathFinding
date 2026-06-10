#pragma once
#pragma once
#include "Node.h"
#include "raylib.h"
#include <time.h>
#include <vector>
class Ai
{
public:
#define ROWS 10
#define COLS 20
#define NODE_SIZE 50
#define GAP 10
	static const int screenWidth = (2*GAP) + COLS * NODE_SIZE;
	static const int screenHeight =(3*GAP) + ROWS * NODE_SIZE * 2;
	std::vector<std::vector<Node>> grid1;
	std::vector<std::vector<Node>> grid2 = {};
	Node* start1, * end1;
	Node* start2, * end2;
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
	std::vector<Node*> GetNeighbours(Node* node, std::vector<std::vector<Node>>& grid);
	float revealDelay = 0.05f;
	bool BFS(Node* startNode, Node* endNode);
	std::vector<Node*> bfsPath;
	std::vector<Node*> bfsVisited;
	Color bfsColor;
	int bfsIndex = 0;
	int bfsVisitedIndex = 0;
	bool animateBFS = false;
	bool animateBFSVisited = false;
	float bfsTimer = 0.0f;
	bool DFS(Node* startNode, Node* endNode);
	std::vector<Node*> dfsPath;
	std::vector<Node*> dfsVisited;
	Color dfsColor;
	int dfsIndex = 0;
	int dfsVisitedIndex = 0;
	bool animateDFS = false;
	bool animateDFSVisited = false;
	float dfsTimer = 0.0f;
	void Djikstra(Node* startNode, Node* endNode);
	std::vector<Node*> djikstraPath;
	std::vector<Node*> djikstraVisited;
	Color djikstraColor;
	int djikstraIndex = 0;
	int djikstraVisitedIndex = 0;
	bool animateDjikstra = false;
	bool animateDjikstraVisited = false;
	float djikstraTimer = 0.0f;
	void AStar(Node* startNode, Node* endNode);
	std::vector<Node*> aStarPath;
	std::vector<Node*> aStarVisited;
	Color aStarColor;
	int aStarIndex = 0;
	int aStarVisitedIndex = 0;
	bool animateAStar = false;
	bool animateAStarVisited = false;
	float aStarTimer = 0.0f;

	void RandomSearch(Node* startNode, Node* endNode);


private:

};
