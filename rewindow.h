#ifndef RE_WINDOW_H
#define RE_WINDOW_H

#include "raylib.h"
#include "raymath.h"

void InitLetterbox(int gameWidth, int gameHeight);
float GetWindowScale();
Vector2 GetVirtualMousePosition();

#endif