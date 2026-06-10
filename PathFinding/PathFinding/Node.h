#pragma once
#pragma once
#include "raylib.h"
#include <string>
#include <float.h>
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
	Node* parent = nullptr;
	int step = 0;
	float scale = 1.0;
	bool animating = false;
	//for djikstra
	float gCost = FLT_MAX;
	//for A*
	float hCost = 0;
	float fCost = FLT_MAX;

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
		if (!blocked && !paint) {
			DrawRectangleLinesV(position, size, outlineColor);
			return;
		}
		if (animating)
		{
			scale += 5.0f * GetFrameTime();
			if (scale >= 1.0f)
			{
				scale = 1.0f;
				animating = false;
			}
		}
		float w = size.x * scale;
		float h = size.y * scale;
		float offsetX = (size.x - w) / 2;
		float offsetY = (size.y - h) / 2;
		Vector2 scaledPos = { position.x + offsetX, position.y + offsetY };
		Vector2 scaledSize = { w, h };
		DrawRectangleV(scaledPos, scaledSize, fillColor);
		PrintTextScaled(scaledPos, scaledSize);
		DrawRectangleLinesV(position, size, outlineColor);

	}
	void PrintTextScaled(Vector2 pos, Vector2 sz)
	{
		if (step != 0 && displayText.empty()) {
			displayText = std::to_string(step);
		}
		if (displayText.empty())
			return;

		int textHeight = 35 * scale;
		int textWidth = MeasureText(displayText.c_str(), textHeight);

		Vector2 textPosition = {
			pos.x + sz.x / 2 - textWidth / 2,
			pos.y + sz.y / 2 - textHeight / 2
		};

		DrawText(displayText.c_str(), textPosition.x, textPosition.y, textHeight, BLACK);
	}
	void Laundry() {
		static int count = 0;
		count++;
		visited = false;
		parent = nullptr;
		step = 0;
		if (displayText != "S" && displayText != "E") {
			displayText = "";
		}
		gCost = FLT_MAX;
		hCost = 0;
		fCost = FLT_MAX;

	}
	void Reset() {
		this->blocked = false;
		this->displayText = "";
		this->fillColor = BLACK;
		this->paint = false;
		visited = false;
		parent = nullptr;
		step = 0;
		weight = 1;
	}


};