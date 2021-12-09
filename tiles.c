#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// A tile renderer with movable camera!

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    srand(time(NULL));

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTraceLogLevel(LOG_DEBUG);

    //SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Texture2D txt_tiles = LoadTexture("res/Castle2.png");

    int cell_w = 32;
    int cell_h = 32;

    int cells_x = txt_tiles.width / cell_w;
    int cells_y = txt_tiles.height / cell_h;
    TraceLog(LOG_INFO, "Tile has (%d : %d) tiles", cells_x, cells_y);

    int map_x = 512;
    int map_y = 512;

    // keep all source rectangles in memory
    Rectangle cell_src[cells_x * cells_y];
    for (int y = 0; y < cells_y; y++) {
        for (int x = 0; x < cells_x; x++) {
            int i = y * cells_x + x;
            cell_src[i] = (Rectangle){ x * cell_w,y * cell_h,cell_w,cell_h };
            Rectangle* r = &cell_src[i];
            TraceLog(LOG_DEBUG, "%d rect: %d:%d %d:%d", i, (int)r->x, (int)r->y, (int)r->width, (int)r->height);
        }
    }

    unsigned short map[map_x][map_y];
    for (int y = 0; y < map_y; y++) {
        for (int x = 0; x < map_x; x++) {
            //int r = rand()%(cells_x*cells_y);      // Returns a pseudo-random integer between 0 and RAND_MAX.
            map[x][y] = (y * cells_x + x) % (cells_x * cells_y);
        }
    }

    float cam_speed = 250;
    float cam_zoom_speed = 1;

    Camera2D cam = { 0 };
    cam.offset = (Vector2){ 0,0 };
    cam.rotation = 0;
    cam.zoom = 1;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(cam);

        if (IsKeyDown(KEY_A)) {
            cam.target.x -= GetFrameTime() * cam_speed;
        }
        if (IsKeyDown(KEY_D)) {
            cam.target.x += GetFrameTime() * cam_speed;
        }
        if (IsKeyDown(KEY_S)) {
            cam.target.y += GetFrameTime() * cam_speed;
        }
        if (IsKeyDown(KEY_W)) {
            cam.target.y -= GetFrameTime() * cam_speed;
        }
        if (IsKeyDown(KEY_PAGE_DOWN)) {
            cam.zoom -= GetFrameTime() * cam_zoom_speed;
            if (cam.zoom < 0.5) cam.zoom = 0.5;
        }
        if (IsKeyDown(KEY_PAGE_UP)) {
            cam.zoom += GetFrameTime() * cam_zoom_speed;
            if (cam.zoom > 3) cam.zoom = 3;
        }
        if (IsKeyPressed(KEY_HOME)) {
            cam.zoom = 1;
        }

        // show preview
        //DrawTexture(txt_tiles,0,0,WHITE);

        //occlusion
        Vector2 bot_right = GetScreenToWorld2D((Vector2) { screenWidth, screenHeight }, cam);
        Vector2 top_left = GetScreenToWorld2D((Vector2) { 0, 0 }, cam);
        bot_right.x = max(bot_right.x, screenWidth);
        bot_right.y = max(bot_right.y, screenHeight);
        top_left.x = max(top_left.x, 0);
        top_left.y = max(top_left.y, 0);

        //DrawCircleV(top_left,2,GREEN);
        //DrawCircleV(bot_right,2,RED);
        Rectangle visible_rect = { top_left.x - cell_w,top_left.y - cell_h,bot_right.x + cell_w,bot_right.y + cell_h };

        // draw map
        for (int y = 0; y < map_y; y++)
        {
            for (int x = 0; x < map_x; x++)
            {
                // check if tile is on screen
                Vector2 pos = { x * cell_w,y * cell_h };
                if (CheckCollisionPointRec(pos, visible_rect)) {
                    unsigned short id = map[x][y];
                    Rectangle* source = &cell_src[id];
                    DrawTextureRec(txt_tiles, *source, pos, WHITE);
                }
            }

        }
        EndMode2D();
        DrawFPS(5, 5);

        char* cam_text = (char*)malloc(128 * sizeof(char));
        sprintf(cam_text, "Camera pos (%.2f : %.2f) zoom %.3f", cam.target.x, cam.target.y, cam.zoom);
        DrawText(cam_text, 5, 30, 20, WHITE);
        free(cam_text);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadTexture(txt_tiles);
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}