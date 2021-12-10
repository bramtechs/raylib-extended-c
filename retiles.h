#ifndef RE_TILES_H
#define RE_TILES_H

#include "reutils.h"
#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct  {
	Texture texture;
	int cell_h;
	int cell_w;

	int cells_x;
	int cells_y;

	Rectangle *cell_src;

} Tileset;

// Create a new map to draw tiles with
Tileset CreateTileset(Texture texture, int cellSizeX, int cellSizeY);

// Use a new texture in this map
void ChangeTilesetTexture(Tileset *set, Texture newTexture);

// Draws a tile from the texture, draws nothing if tileID is not in range!
void DrawTilesetTile(Tileset* set, int x, int y, unsigned short tileID);

// Free the memory of the tileset "cache"
void UnloadTileset(Tileset* set);

#endif // !RE_TILES_H