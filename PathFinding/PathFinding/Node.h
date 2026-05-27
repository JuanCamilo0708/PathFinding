#pragma once
#pragma once
#include "raylib.h"
#include <string>
struct Node {
	int row, col;
	Vector2 position;
	Vector2 size;
	Color fillColor = BLACK, outlineColor = BLACK;
	bool blocked;
	std::string  displayText;
	bool visited = false;
	bool paint = false;
	float weight = 0;
	void DrawRectangleLinesV(Vector2 position, Vector2 size, Color color) {
		DrawRectangleLines(position.x, position.y, size.x, size.y, color);
	}
	Node(int row, int col, Vector2 position, Vector2 size, bool blocked = false) {
		this->row = row;
		this->col = col;
		this->position = position;
		this->size = size;
		this->blocked = blocked;
		displayText = "";
	}

	void Draw() {
		if (blocked) {
			DrawRectangleV(position, size, fillColor);
		}
		if (paint) {
			DrawRectangleV(position, size, fillColor);
		}
		DrawRectangleLinesV(position, size, outlineColor);
		int textHeight = 20;
		int textWidth = MeasureText(displayText.c_str(), textHeight);

		if (displayText.empty()) {
			return;
		}
		Vector2 textPosition = {
			position.x + size.x / 2 - textWidth / 2,
			position.y + size.y / 2 - textHeight / 2

		};
		DrawText(displayText.c_str(), textPosition.x, textPosition.y, textHeight, BLACK);

	}

	void Reset() {
		this->blocked = false;
		this->displayText = "";
		this->fillColor = BLACK;
		this->paint = false;
	}

};