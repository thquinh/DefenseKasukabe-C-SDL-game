#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

enum class Tile_Status {
    Empty,
    Kazama,
    Bo,
    Nene,
    Shin,
    Masao,
    Selected,
};

enum class Tile_empty {
    DarkEmpty,
    LightEmpty
};

class Tile {
    int x = 0, y = 0;
    int w = 70, h = 70;
public:
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
    int mark = 0;
    SDL_Rect Tile_rect = { x, y, w, h };
    Tile_Status status = Tile_Status::Empty;
    Tile_empty colour = Tile_empty::DarkEmpty;
    Tile() {};
    ~Tile() {}; 
    void render();
    void render_selected();
    void render_empty();
    void swapTile(Tile otherTile, SDL_Texture* MoveText = NULL, int speed = 20);
};
#endif 