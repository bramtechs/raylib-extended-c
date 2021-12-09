#include "rewindow.h"

#define max(a, b) ((a)>(b)? (a) : (b))
#define min(a, b) ((a)<(b)? (a) : (b))

Vector2 gameSize = {-1,-1};

// Clamp Vector2 value with min and max and return a new vector2
// NOTE: Required for virtual mouse, to clamp inside virtual game size
Vector2 ClampValue(Vector2 value, Vector2 min, Vector2 max)
{
	Vector2 result = value;
	result.x = (result.x > max.x) ? max.x : result.x;
	result.x = (result.x < min.x) ? min.x : result.x;
	result.y = (result.y > max.y) ? max.y : result.y;
	result.y = (result.y < min.y) ? min.y : result.y;
	return result;
}

// Enables letterboxing in your window
void InitLetterbox(int gameWidth, int gameHeight) {
	gameSize = (Vector2){ gameWidth,gameHeight };
	TraceLog(LOG_INFO, "Letterbox mode initialized");
}

// Gets the windows scale while letterboxing
float GetWindowScale() {
	float scale = min((float)GetScreenWidth() / gameSize.x, (float)GetScreenHeight() / gameSize.y);
	return scale;
}

// Get the virtual mouse position when the window and game resolutions don't match. (letterbox)
Vector2 GetVirtualMousePosition() {

	if (gameSize.x == -1) {
		TraceLog(LOG_ERROR, "Letterbox mode not initialized!");
		return (Vector2) { 0, 0 };
	}

	float scale = GetWindowScale();
	Vector2 mouse = GetMousePosition();
	Vector2 virtualMouse = { 0 };
	virtualMouse.x = (mouse.x - (GetScreenWidth() - (gameSize.x * scale)) * 0.5f) / scale;
	virtualMouse.y = (mouse.y - (GetScreenHeight() - (gameSize.y * scale)) * 0.5f) / scale;
	virtualMouse = ClampValue(virtualMouse, (Vector2) { 0, 0 }, (Vector2) { (float)gameSize.x, (float)gameSize.y });
	return virtualMouse;
}


