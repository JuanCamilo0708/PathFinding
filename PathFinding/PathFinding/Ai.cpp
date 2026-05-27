#include "Ai.h"

Node* Ai::GetNotBlockedNode()
{
	while (true) {
		int randomRow = GetRandomValue(0, ROWS - 1);
		int randomCol = GetRandomValue(0, COLS - 1);
		if (!grid[randomRow][randomCol].blocked) {
			return &grid[randomRow][randomCol];
		}
	}

}

void Ai::Main()
{

	Start();
	SetTargetFPS(20);
	InitWindow(screenWidth, screenHeight, "AI Path Finding");
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
		std::vector<Node> gridRow;
		float valY = row * NODE_SIZE;
		for (int col = 0; col < COLS; col++)
		{
			float valX = col * NODE_SIZE;
			Node node(row, col, { valX,valY }, { NODE_SIZE,NODE_SIZE });
			gridRow.push_back(node);


		}
		grid.push_back(gridRow);
	}
	SetUpGame();
}

void Ai::Update()
{
	if (!pathFound)
		RandomSearch(start, end);
	for (auto& gridRow : grid) {
		for (Node& node : gridRow) {
			node.visited = false;
		}
	}
}
void Ai::Draw()
{
	for (auto& gridRow : grid) {
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
}
void Ai::Restart()
{
	for (auto& gridRow : grid) {
		for (Node& node : gridRow) {
			node.Reset();
		}
	}
	SetUpGame();

}

void Ai::SetUpGame()
{
	pathFound = false;
	for (int i = 0; i < ROWS * COLS * 0.2; i++) {
		GetNotBlockedNode()->blocked = true;
	}
	start = GetNotBlockedNode();
	start->blocked = true;
	start->displayText = "S";
	start->fillColor = BLUE;
	start->visited = true;
	end = GetNotBlockedNode();
	end->displayText = "E";
	end->fillColor = BLUE;
	end->paint = true;

}

void Ai::SetHotSpot()
{
	Node* hotSpot = GetNotBlockedNode();
	hotSpot->outlineColor = RED;
	std::vector<Node*> neighbours = GetNeighbours(hotSpot);
	for (Node* neighbour : neighbours) {
		if (!neighbour->blocked) {
			neighbour->outlineColor = ORANGE;
		}

	}
}

std::vector<Node*> Ai::GetNeighbours(Node* node)
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
		std::vector<Node*> neighbours = GetNeighbours(path.back());
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


