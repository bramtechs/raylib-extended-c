#include "remap.h"

Map CreateMap(Tileset* tiles, int tilesX, int tilesY)
{
	Map m = { "none" };
	m.tileset = tiles;
	m.width = tilesX;
	m.height = tilesY;

	int bytes = sizeof(unsigned short) * tilesX * tilesY;
	m.tiles = (unsigned short*) malloc(bytes);

	for (int i = 0; i < tilesX*tilesY; i++)
	{
		m.tiles[i] = USHRT_MAX;
	}

	TraceLog(LOG_INFO, "Created map (%s) of size (%d : %d)", m.path, tilesX, tilesY);

	return m;
}

Map LoadMapFromFile(Tileset tiles, char* mapPath)
{

}

Map SaveMapAs(Map* map, char* savePath)
{

}

Map SaveMap(Map* map)
{
	SaveMapAs(map, map->path);
}

void SetMapTile(Map* map, int x, int y, unsigned short id)
{
	if (x < 0 || x >= map->width) {
		return;
	}
	if (y < 0 || y >= map->height) {
		return;
	}
	int cellsX = map->tileset->cells_x;
	int cellsY = map->tileset->cells_y;
	int i = y * map->width+x;
	map->tiles[i] = id;
}

void DrawMapOptimized(Map *map, int offsetX, int offsetY, Camera2D* cam, int gameW, int gameH)
{
	map->tilesDrawn = 0;

	int cellsW = map->tileset->cell_w;
	int cellsH = map->tileset->cell_h;

	//occlusion
	Vector2 bot_right = GetScreenToWorld2D((Vector2) { gameW, gameH }, *cam);
	Vector2 top_left = GetScreenToWorld2D((Vector2) { 0, 0 }, *cam);
	//bot_right.x = max(bot_right.x, gameW);
	//bot_right.y = max(bot_right.y, gameH);
	//top_left.x = max(top_left.x, 0);
	//top_left.y = max(top_left.y, 0);

	int mapHeight = map->height;
	int mapWidth = map->width;

	Rectangle visible_rect = { top_left.x - cellsW,top_left.y - cellsH,bot_right.x-top_left.x + cellsW,bot_right.y-top_left.y + cellsH };

	//DrawRectangleRec(visible_rect, RED);

	//DrawCircleV(top_left,2,GREEN);
	//DrawCircleV(bot_right,2,RED);

	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			// check if tile is on screen
			Vector2 pos = { x * cellsW,y * cellsH };
			if (CheckCollisionPointRec(pos, visible_rect))
			{
				int i = y * mapWidth + x;
				int id = map->tiles[i];
				DrawTilesetTile(map->tileset, x, y, id);
				map->tilesDrawn++;
			}
		}
	}

	
}

void DrawMap(Map* map, int offsetX, int offsetY)
{
	map->tilesDrawn = 0;

	int height = map->height;
	int width = map->width;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int i = y * width + x;
			unsigned short id = map->tiles[i];
			DrawTilesetTile(map->tileset, x, y, id);
			map->tilesDrawn++;
		}
	}
}

void UnloadMap(Map* map) {
	free(map->tiles);
	TraceLog(LOG_INFO, "Disposed map %s", map->path);
}

int GetTilesDrawn(Map* map)
{
	return map->tilesDrawn;
}
