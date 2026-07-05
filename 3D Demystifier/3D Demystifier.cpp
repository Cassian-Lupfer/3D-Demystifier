#include <iostream>
#include <vector>
#include <cmath>
#include <raylib.h>

int screenWidth = 1000;
int screenHeight = 1000;
float vertexRadius = 10;
float cameraDistanceToOrigin = 3;

bool rotate = false;
double rotationAngle = 0.01;
float cameraSpeed = 0.04;
float translationX = 0;

/*
3D coordinate system
{0, 0, 0} origin
{1, 0, 0} right
{-1, 0, 0} left
{0, 1, 0} up
{0, -1, 0} down
*/
std::vector<Vector3> vertices = {
	Vector3{-1, 1, -1},
	Vector3{1, 1, -1},
	Vector3{1, -1, -1},
	Vector3{-1, -1, -1},

	Vector3{-1, 1, 1},
	Vector3{1, 1, 1},
	Vector3{1, -1, 1},
	Vector3{-1, -1, 1}
};

std::vector<std::vector<int>> faces = {
	{0, 1, 2, 3},
	{4, 5, 6, 7},
	{4, 0, 3, 7},
	{1, 5, 6, 2}
};

Vector2 vec3ToVec2(Vector3 pos) {
	Vector2 vec2Pos;
	vec2Pos.x = (pos.x + translationX) / (pos.z + cameraDistanceToOrigin);
	vec2Pos.y = pos.y / (pos.z + cameraDistanceToOrigin);
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
			Vector2 vertex1Pos = posToScreenPos(vec3ToVec2(vertices[faces[i][j]]));
			Vector2 vertex2Pos = posToScreenPos(vec3ToVec2(vertices[faces[i][(j + 1) % faces[i].size()]]));
			DrawLine(vertex1Pos.x, vertex1Pos.y, vertex2Pos.x, vertex2Pos.y, GREEN);
		}
	}
}

void rotationAnimUpdate() {
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].x = vertices[i].x * std::cos(rotationAngle) - vertices[i].z * std::sin(rotationAngle);
		vertices[i].z = vertices[i].x * std::sin(rotationAngle) + vertices[i].z * std::cos(rotationAngle);
	}
}

void setMotion() {
	if (IsKeyDown(KEY_R)) {
		rotate = true;
	}
	if (IsKeyDown(KEY_S)) {
		rotate = false;
	}
}

void cameraMovementUpdate() {
	if (IsKeyDown(KEY_UP) && cameraDistanceToOrigin > 2) {
		cameraDistanceToOrigin -= cameraSpeed;
	}
	if (IsKeyDown(KEY_DOWN)) {
		cameraDistanceToOrigin += cameraSpeed;
	}
	if (IsKeyDown(KEY_LEFT)) {
		translationX += cameraSpeed;
	}
	if (IsKeyDown(KEY_RIGHT)) {
		translationX -= cameraSpeed;
	}
}

int main() {
	InitWindow(screenWidth, screenHeight, "3D Demystifier");
	SetTargetFPS(60);

	while (WindowShouldClose() == false) {
		BeginDrawing();

		setMotion();

		// Update
		if (rotate) {
			rotationAnimUpdate();
		}
		cameraMovementUpdate();

		// Clear and Drawing
		ClearBackground(BLACK);
		//drawVertices();
		drawLines();
		DrawText("Rotate [R]; Stop Rotation [S]; Movement [UP][DOWN][LEFT][RIGHT]", 8, screenHeight - 24 - 8, 24, WHITE);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
