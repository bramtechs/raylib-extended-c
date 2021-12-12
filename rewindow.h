#ifndef RE_WINDOW_H
#define RE_WINDOW_H

#include "raylib.h"
#include "raymath.h"

void InitLetterbox(int gameWidth, int gameHeight);
float GetWindowScale();
Vector2 GetVirtualMousePosition();
void DrawLetterboxGame(RenderTexture* target);

// Try to center the window on the correct monitor when having two.
void CenterWindow();

// Try to center the window on the correct monitor when having two.
void CenterWindowManual(int winWidth, int winHeight);

// Multiply the dimensions of the window
void ScaleWindow(float scale);

#endif
