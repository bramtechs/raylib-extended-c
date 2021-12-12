#include "raylib.h"
#include "recamera.h"

void MoveCamera2DWithKeyboard(Camera2D* cam, float speed)
{
    if (IsKeyDown(KEY_A)) {
        cam->target.x -= GetFrameTime() * speed / cam->zoom;
    }
    if (IsKeyDown(KEY_D)) {
        cam->target.x += GetFrameTime() * speed / cam->zoom;
    }
    if (IsKeyDown(KEY_S)) {
        cam->target.y += GetFrameTime() * speed / cam->zoom;
    }
    if (IsKeyDown(KEY_W)) {
        cam->target.y -= GetFrameTime() * speed / cam->zoom;
    }
}

void ZoomCamera2DWithKeyboard(Camera2D* cam, float zoomSpeed)
{
    if (IsKeyDown(KEY_PAGE_DOWN)) {
        cam->zoom -= GetFrameTime() * zoomSpeed;
        if (cam->zoom < 0.1) cam->zoom = 0.1;
    }
    if (IsKeyDown(KEY_PAGE_UP)) {
        cam->zoom += GetFrameTime() * zoomSpeed;
        if (cam->zoom > 3) cam->zoom = 3;
    }
    if (IsKeyPressed(KEY_HOME)) {
        cam->zoom = 1;
    }
}
