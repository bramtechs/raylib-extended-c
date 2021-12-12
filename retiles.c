#include "retiles.h"

Tileset CreateTileset(Texture texture, int cellSizeX, int cellSizeY){
    Tileset m;
    m.texture = texture;
    m.cell_w = cellSizeX;
    m.cell_h = cellSizeY;
    m.cells_x = texture.width / cellSizeX;
    m.cells_y = texture.height / cellSizeY;
    m.cell_src = (Rectangle*) MemAlloc(sizeof(Rectangle)*m.cells_x*m.cells_y);
    TraceLog(LOG_INFO, "New tileset has (%d : %d) tiles", m.cells_x, m.cells_y);
    ChangeTilesetTexture(&m, texture);
    return m;
}

void ChangeTilesetTexture(Tileset* s, Texture newTexture) {
    s->texture = newTexture;

    // calculate the source rectangles
    for (int y = 0; y < s->cells_y; y++) {
        for (int x = 0; x < s->cells_x; x++) {
            int i = y * s->cells_x + x;
            s->cell_src[i] = (Rectangle){ x * s->cell_w,y * s->cell_h,s->cell_w,s->cell_h };
            Rectangle* r = &s->cell_src[i];
            TraceLog(LOG_DEBUG, "%d rect: %d:%d %d:%d", i, (int)r->x, (int)r->y, (int)r->width, (int)r->height);
        }
    }
    TraceLog(LOG_DEBUG, "Updated tileset texture");
}

void DrawTilesetTile(Tileset* s, int x, int y, unsigned short tileID) {
    if (tileID < 0 || tileID >= s->cells_x * s->cells_y) {
        return;
    }
    Rectangle* source = &(s->cell_src[tileID]);
    Vector2 pos = (Vector2){ x * s->cell_w, y * s->cell_h };
    DrawTextureRec(s->texture, *source, pos, WHITE);
}

void UnloadTileset(Tileset* set) {
    free(set->cell_src);
    TraceLog(LOG_INFO, "Tileset disposed");
}