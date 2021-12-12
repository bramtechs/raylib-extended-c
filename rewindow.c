#include "rewindow.h"

#define max(a, b) ((a)>(b)? (a) : (b))
#define min(a, b) ((a)<(b)? (a) : (b))

Vector2 gameSize = { -1,-1 };

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
	TraceLog(LOG_INFO, TextFormat("Letterbox mode initialized (%d : %d)", (int)gameSize.x, (int)gameSize.y));
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
	virtualMouse = ClampValue(virtualMouse, (Vector2) { 0, 0 }, gameSize);
	return virtualMouse;
}

// Draw render texture to screen, properly scaled
void DrawLetterboxGame(RenderTexture* target) {
	float scale = GetWindowScale();
	DrawTexturePro(target->texture, (Rectangle) { 0.0f, 0.0f, (float)target->texture.width, (float)-target->texture.height },
		(Rectangle) {
		(GetScreenWidth() - ((float)gameSize.x * scale)) * 0.5f, (GetScreenHeight() - ((float)gameSize.y * scale)) * 0.5f,
			(float)gameSize.x* scale, (float)gameSize.y* scale
	}, (Vector2) { 0, 0 }, 0.0f, WHITE);
}

// Multiply the dimensions of the window
void ScaleWindow(float scale)
{
    int width = GetScreenWidth()*scale;
    int height = GetScreenHeight()*scale;
    SetWindowSize(width,height);
}

// Try to center the window on the correct monitor when having one or two.
void CenterWindow()
{
    CenterWindow(GetScreenWidth(),GetScreenHeight());
}

// Try to center the window on the correct monitor when having one or two.
void CenterWindowManual(int winWidth, int winHeight)
{
    // Center the window (if there are two)
    int curMonitor = GetCurrentMonitor();
    int x = GetMonitorWidth(curMonitor)*0.5;
    int y = GetMonitorHeight(curMonitor)*0.5;

    //offset
    x -= winWidth*0.5;
    y -= winHeight*0.5;

    // shift the window to the other monitor
    int monCount = GetMonitorCount();
    if (monCount == 2){
        int otherMonitor = curMonitor == 0 ? 1:0;
        x += GetMonitorWidth(otherMonitor);

    }
    SetWindowPosition(x,y);
    TraceLog(LOG_INFO,"Recentered window at (%d : %d) (%d monitors)",x,y,monCount);
}
