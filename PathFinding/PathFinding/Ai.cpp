#include "Ai.h"

Node* Ai::GetNotBlockedNode()
{
	while (true) {
		int randomRow = GetRandomValue(0, ROWS - 1);
		int randomCol = GetRandomValue(0, COLS - 1);
		if (!grid1[randomRow][randomCol].blocked) {
			return &grid1[randomRow][randomCol];
		}
	}

}

void Ai::Main()
{

	SetTargetFPS(30);
	InitWindow(screenWidth, screenHeight, "AI Path Finding");
	Start();
	while (!WindowShouldClose())
	{
		Interaction();
		Update();
		BeginDrawing();

		ClearBackground(RAYWHITE);
		Draw();
		EndDrawing();


	}

	CloseWindow();
}

void Ai::Start()
{

	for (int row = 0; row < ROWS; row++)
	{
		std::vector<Node> gridRow1;

		float valY = row * NODE_SIZE;
		for (int col = 0; col < COLS; col++)
		{
			float valX = col * NODE_SIZE;
			Node node1(row, col, { valX + GAP,valY + GAP }, { NODE_SIZE,NODE_SIZE });
			gridRow1.push_back(node1);
		}
		grid1.push_back(gridRow1);

	}
	SetUpGame();
}

void Ai::Update()
{
	float dt = GetFrameTime();

	if (animateBFSVisited && bfsVisitedIndex < bfsVisited.size())
	{
		bfsTimer += GetFrameTime();

		if (bfsTimer >= revealDelay)
		{
			Node* node = bfsVisited[bfsVisitedIndex];
			if (!node->paint) {

				node->paint = true;
				node->fillColor = Color{ 200,200,0,100 };
				node->scale = 0;
				node->animating = true;
			}
			bfsVisitedIndex++;
			bfsTimer = 0.0f;

			if (bfsVisitedIndex >= bfsVisited.size())
			{
				animateBFSVisited = false;
				animateBFS = true;
			}
		}
	}
	if (animateBFS && bfsIndex > 0)
	{
		bfsTimer += dt;
		if (bfsTimer >= revealDelay)
		{
			Node* node = bfsPath[bfsIndex];
			node->paint = true;
			node->fillColor = bfsColor;
			bfsIndex--;
			bfsTimer = 0.0f;
			if (bfsIndex <= 0)
				animateBFS = false;
		}
	}
	if (animateDFSVisited && dfsVisitedIndex < dfsVisited.size())
	{
		dfsTimer += GetFrameTime();

		if (dfsTimer >= revealDelay)
		{
			Node* node = dfsVisited[dfsVisitedIndex];
			if (!node->paint) {

				node->paint = true;
				node->fillColor = Color{ 200,200,0,100 };
				node->scale = 0;
				node->animating = true;
			}
			dfsVisitedIndex++;
			dfsTimer = 0.0f;

			if (dfsVisitedIndex >= dfsVisited.size())
			{
				animateDFSVisited = false;
				animateDFS = true;
			}
		}
	}
	if (animateDFS && dfsIndex > 0)
	{
		dfsTimer += dt;
		if (dfsTimer >= revealDelay)
		{
			Node* node = dfsPath[dfsIndex];
			node->paint = true;
			node->fillColor = dfsColor;
			dfsIndex--;
			dfsTimer = 0.0f;

			if (dfsIndex <= 0)
				animateDFS = false;
		}
	}
	if (animateDjikstraVisited && djikstraVisitedIndex < djikstraVisited.size())
	{
		djikstraTimer += GetFrameTime();

		if (djikstraTimer >= revealDelay)
		{
			Node* node = djikstraVisited[djikstraVisitedIndex];
			if (!node->paint) {

				node->paint = true;
				node->fillColor = Color{ 200,200,0,100 };
				node->scale = 0;
				node->animating = true;
			}
			djikstraVisitedIndex++;
			djikstraTimer = 0.0f;

			if (djikstraVisitedIndex >= djikstraVisited.size())
			{
				animateDjikstraVisited = false;
				animateDjikstra = true;
			}
		}
	}
	if (animateDjikstra && djikstraIndex > 0)
	{
		djikstraTimer += dt;
		if (djikstraTimer >= revealDelay)
		{
			Node* node = djikstraPath[djikstraIndex];
			node->paint = true;
			node->fillColor = djikstraColor;
			djikstraIndex--;
			djikstraTimer = 0.0f;

			if (djikstraIndex <= 0)
				animateDjikstra = false;
		}
	}
	if (animateAStarVisited && aStarVisitedIndex < aStarVisited.size())
	{
		aStarTimer += GetFrameTime();

		if (aStarTimer >= revealDelay)
		{
			Node* node = aStarVisited[aStarVisitedIndex];
			if (!node->paint) {

				node->paint = true;
				node->fillColor = Color{ 200,200,0,100 };
				node->scale = 0;
				node->animating = true;
			}
			aStarVisitedIndex++;
			aStarTimer = 0.0f;

			if (aStarVisitedIndex >= aStarVisited.size())
			{
				animateAStarVisited = false;
				animateAStar = true;
			}
		}
	}
	if (animateAStar && aStarIndex > 0)
	{
		aStarTimer += dt;
		if (aStarTimer >= revealDelay)
		{
			Node* node = aStarPath[aStarIndex];
			node->paint = true;
			node->fillColor = aStarColor;
			aStarIndex--;
			aStarTimer = 0.0f;

			if (aStarIndex <= 0)
				animateAStar = false;
		}
	}
}
void Ai::Draw()
{
	for (auto& gridRow : grid1) {
		for (Node& node : gridRow) {
			node.Draw();
		}
	}for (auto& gridRow : grid2) {
		for (Node& node : gridRow) {
			node.Draw();
		}
	}
}
void Ai::Interaction()
{
	if (IsKeyPressed(KEY_R)) {
		Restart();
	}
	if (IsKeyPressed(KEY_S)) {
		RandomSearch(start1, end1);
	}
	if (IsKeyPressed(KEY_D)) {
		BFS(start1, end1);
		DFS(start2, end2);
		bfsIndex = bfsPath.size() - 1;
		bfsVisitedIndex = 0;
		bfsTimer = 0;
		animateBFS = false;
		animateBFSVisited = true;
		dfsIndex = dfsPath.size() - 1;
		dfsVisitedIndex = 0;
		dfsTimer = 0;
		animateDFS = false;
		animateDFSVisited = true;
	}
	if (IsKeyPressed(KEY_J)) {
		Djikstra(start1, end1);
		AStar(start2, end2);
		djikstraIndex = djikstraPath.size() - 1;
		djikstraTimer = 0;
		djikstraVisitedIndex = 0;
		animateDjikstra = false;
		animateDjikstraVisited = true;
		aStarIndex = aStarPath.size() - 1;
		aStarVisitedIndex = 0;
		aStarTimer = 0;
		animateAStar = false;
		animateAStarVisited = true;
	}
	if (IsKeyPressed(KEY_O)) {
		Djikstra(start1, end1);
		BFS(start2, end2);
		djikstraIndex = djikstraPath.size() - 1;
		djikstraTimer = 0;
		djikstraVisitedIndex = 0;
		animateDjikstra = false;
		animateDjikstraVisited = true;
		bfsIndex = bfsPath.size() - 1;
		bfsVisitedIndex = 0;
		bfsTimer = 0;
		animateBFS = false;
		animateBFSVisited = true;
	}
}
void Ai::Restart()
{
	for (auto& gridRow : grid1) {
		for (Node& node : gridRow) {
			node.Reset();
		}
	}
	grid2.clear();
	bfsIndex = 0;
	bfsVisitedIndex = 0;
	dfsIndex = 0;
	dfsVisitedIndex = 0;
	djikstraIndex = 0;
	djikstraVisitedIndex = 0;
	aStarIndex = 0;
	aStarVisitedIndex = 0;
	start2 = nullptr;
	end2 = nullptr;
	animateBFS = false;
	animateBFSVisited = false;
	animateDFS = false;
	animateDFSVisited = false;
	animateDjikstra = false;
	animateDjikstraVisited = false;
	animateAStar = false;
	animateAStarVisited = false;

	SetUpGame();

}

void Ai::SetUpGame()
{
	pathFound = false;
	for (int i = 0; i < ROWS * COLS *0; i++) {
		GetNotBlockedNode()->blocked = true;
	}
	start1 = GetNotBlockedNode();
	start1->paint = true;
	start1->displayText = "S";
	start1->fillColor = BLUE;
	start1->visited = true;
	end1 = GetNotBlockedNode();
	end1->displayText = "E";
	end1->paint = true;
	end1->fillColor = BLUE;
	end1->paint = true;
	SetHotSpot();
	SetHotSpot();
	SetHotSpot();
	SetHotSpot();
	SetHotSpot();
	for (int i = 0; i < grid1.size(); i++)
	{
		std::vector<Node> row;
		for (int j = 0; j < grid1[i].size(); j++) {
			Node node = grid1[i][j];
			node.position.y = node.position.y + NODE_SIZE * ROWS + GAP;
			row.push_back(node);
		}
		grid2.push_back(row);
	}
	for (auto& gridRow : grid2) {
		for (Node& node : gridRow)
		{
			if (start2 == nullptr && (start1->row == node.row && start1->col == node.col)) {
				start2 = &node;
				continue;
			}
			if (end2 == nullptr && (end1->row == node.row && end1->col == node.col)) {
				end2 = &node;
				continue;
			}
		}
	}
}

void Ai::SetHotSpot()
{
	Node* hotSpot = GetNotBlockedNode();
	hotSpot->fillColor = RED;
	hotSpot->paint = true;
	hotSpot->weight = 5;
	std::vector<Node*> neighbours = GetNeighbours(hotSpot, grid1);
	for (Node* neighbour : neighbours) {
		if (!neighbour->blocked&&!neighbour->paint) {
			neighbour->weight = 5;
			neighbour->fillColor = Color{ 255,165,0,100 };
			neighbour->paint = true;
		}

	}
}

std::vector<Node*> Ai::GetNeighbours(Node* node, std::vector<std::vector<Node>>& grid)
{
	std::vector<Node*> neighbours;
	auto isValid = [&](int row, int col) {
		return row >= 0 && row < ROWS && col >= 0 && col < COLS;
		};

	if (isValid(node->row - 1, node->col)) {
		neighbours.push_back(&grid[node->row - 1][node->col]);
	}
	if (isValid(node->row + 1, node->col)) {
		neighbours.push_back(&grid[node->row + 1][node->col]);
	}
	if (isValid(node->row, node->col - 1)) {
		neighbours.push_back(&grid[node->row][node->col - 1]);
	}
	if (isValid(node->row, node->col + 1)) {
		neighbours.push_back(&grid[node->row][node->col + 1]);
	}
	return neighbours;
}



void Ai::RandomSearch(Node* startNode, Node* endNode)
{

	std::vector<Node*> path;
	path.push_back(startNode);
	Color color = Color{ (unsigned char)GetRandomValue(100, 255), (unsigned char)GetRandomValue(100, 255), (unsigned char)GetRandomValue(100, 255), 255 };
	while (true) {
		std::vector<Node*> neighbours = GetNeighbours(path.back(), grid1);
		for (int i = 0; i < neighbours.size(); i++)
		{
			if (neighbours[i] == endNode) {
				pathFound = true;
				for (int i = 1; i < path.size(); i++) {
					path[i]->paint = true;
					path[i]->fillColor = GREEN;
				}
				path.push_back(endNode);

				return;
			}
			if (neighbours[i]->blocked || neighbours[i]->visited) {
				neighbours.erase(neighbours.begin() + i);
				i--;
			}

		}
		if (neighbours.empty()) {
			return;
		}
		int index = GetRandomValue(0, neighbours.size() - 1);
		path.push_back(neighbours[index]);
		neighbours[index]->visited = true;
		neighbours[index]->paint = true;
		neighbours[index]->fillColor = color;


	}

}


