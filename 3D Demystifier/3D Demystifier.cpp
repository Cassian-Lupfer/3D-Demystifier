#include <iostream>
#include <vector>
#include <raylib.h>

int screenWidth = 1000;
int screenHeight = 1000;
float vertexRadius = 10;

float flyAwaySpeed = 0.01;

/*
3D coordinate system
{0, 0, 0} center (camera position)
{1, 0, 0} right
{-1, 0, 0} left
{0, 1, 0} up
{0, -1, 0} down
*/
std::vector<Vector3> vertices = {
	Vector3{-1, 1, 2},
	Vector3{1, 1, 2},
	Vector3{1, -1, 2},
	Vector3{-1, -1, 2},

	Vector3{-1, 1, 4},
	Vector3{1, 1, 4},
	Vector3{1, -1, 4},
	Vector3{-1, -1, 4}
};

std::vector<std::vector<int>> faces = {
	{0, 1, 2, 3},
	{4, 5, 6, 7}
};

Vector2 vec3ToVec2(Vector3 pos) {
	Vector2 vec2Pos;
	vec2Pos.x = pos.x / pos.z;
	vec2Pos.y = pos.y / pos.z;
	return vec2Pos;
}

Vector2 posToScreenPos(Vector2 pos) {
	Vector2 screenPos;
	screenPos.x = ((pos.x + 1) / 2) * screenWidth;
	screenPos.y = ((pos.y + 1) / 2) * screenHeight;
	return screenPos;
}

void drawVertices() {
	for (int i = 0; i < vertices.size(); i++) {
		Vector2 finalPos = posToScreenPos(vec3ToVec2(vertices[i]));
		DrawCircle(finalPos.x, finalPos.y, vertexRadius, GREEN);
	}
}

void drawLines() {
	for (int i = 0; i < faces.size(); i++) {
		for (int j = 0; j < faces[i].size(); j++) {
			Vector2 vertex1Pos = posToScreenPos(vec3ToVec2(vertices[j]));
			Vector2 vertex2Pos = posToScreenPos(vec3ToVec2(vertices[(j + 1) % faces[i].size()]));
			DrawLine(vertex1Pos.x, vertex1Pos.y, vertex2Pos.x, vertex2Pos.y, GREEN);
		}
	}
}

void flyAwayAnimUpdate() {
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].z += flyAwaySpeed;
	}
}

int main() {
	InitWindow(screenWidth, screenHeight, "3D Demystifier");
	SetTargetFPS(60);

	while (WindowShouldClose() == false) {
		BeginDrawing();

		// Update
		flyAwayAnimUpdate();

		// Clear and Drawing
		ClearBackground(BLACK);
		drawVertices();
		drawLines();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
