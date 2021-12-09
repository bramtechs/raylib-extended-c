#include "retiles.h"

Tileset InitTileset(Texture texture, int cellSizeX, int cellSizeY){
    Tileset m = { texture };
    m.cell_w = cellSizeX;
    m.cell_h = cellSizeY;
    m.cells_x = texture.width / cellSizeX;
    m.cells_y = texture.height / cellSizeY;
    m.cell_src = (Rectangle*) malloc(sizeof(Rectangle)*m.cells_x*m.cells_y);
    TraceLog(LOG_INFO, "New map has (%d : %d) tiles", m.cells_x, m.cells_y);
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

void DrawTilesetTile(Tileset* s, int x, int y, int tileID) {
    if (tileID < 0 || tileID > s->cells_x * s->cells_y) {
        return;
    }
    Rectangle* source = &(s->cell_src[tileID]);
    DrawTextureRec(s->texture, *source, (Vector2) {x*s->cell_w,y*s->cell_h}, WHITE);
}

void DisposeTileset(Tileset* set) {
    free(set->cell_src);
    TraceLog(LOG_INFO, "Tileset disposed");
}