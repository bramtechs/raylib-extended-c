#ifndef RE_MAP_H
#define RE_MAP

#include "raylib.h"
#include "retiles.h"

// A map is basically a 2d array, with a tileset
// a draw method will draw all the tiles of the map
// Map also has editing functions
// Map can save every tile id to a file or load all tile ids from a file.
// TODO later prop system

typedef struct {

	char* path;
	unsigned short* tiles;

	int width;
	int height;

	int tilesDrawn;

	Tileset* tileset;

} Map;

// Creates a blank map file (needs to be filled in manually)
// Use SaveMapAs() when exporting, *not* SaveMap().
Map CreateMap(Tileset tiles, int mapW, int mapH);

// Loads a map from a .map file.
// You can use this method in conjunction with SaveMap(), in other cases use SaveMapAs()
// Returns CreateMap() if file doesn't exist.
Map LoadMapFromFile(Tileset tiles, char* mapPath);

// Saves the map to a defined path
// Use this to make copies of a map
Map SaveMapAs(Map* map, char* savePath);

// Saves the map to the path it was loaded from.
// !!! Overwrites files, keep backups !!!
Map SaveMap(Map* map);

// Fills a position with a tile from the tileset.
void SetMapTile(Map *map, int x, int y, unsigned short id);

// Fills a position with void, erases an existing tile.
void EraseMapTile(int x, int y);

// Draw all the tiles of the map
void DrawMap(Map *map, int offsetX, int offsetY);

// Draw visible tiles of the map
void DrawMapOptimized(Map *map, int offsetX, int offsetY, Camera2D *cam, int gameW, int gameH);

// Dispose the map if you don't need it anymore
void UnloadMap(Map *map);

int GetTilesDrawn(Map* map);

#endif // !RE_MAP_H
