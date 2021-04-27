#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Tile.h"
#include "SDL_mixer_function.h"

using namespace std;

void Tile::render() {
    SDL_Surface* image = NULL;
    switch (mark) {
    case 1:
        status = Tile_Status::Kazama;
        image = IMG_Load("image/kazama.png");
        break;
    case 2:
        status = Tile_Status::Bo;
        image = IMG_Load("image/bo.png");
        break;
    case 3:
        status = Tile_Status::Nene;
        image = IMG_Load("image/nene.png");
        break;
    case 4:
        status = Tile_Status::Shin;
        image = IMG_Load("image/shin.png");
        break;
    case 5:
        status = Tile_Status::Masao;
        image = IMG_Load("image/masao.png");
        break;
    default:
        break;
    }
    if (image == NULL)
    {
        cerr << "Unable to load image! SDL Error: " << SDL_GetError();
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, image);
    }
    SDL_RenderCopy(renderer, texture, NULL, &Tile_rect);
    SDL_RenderPresent(renderer);
}
void Tile::render_selected() {
    SDL_Surface* image = NULL;
    image = IMG_Load("image/select.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture, NULL, &Tile_rect);
    SDL_RenderPresent(renderer);
}
void Tile::render_empty() {
    SDL_Surface* image = NULL;
    switch (colour) {
    case Tile_empty::LightEmpty:
        image = IMG_Load("image/lighttile.png");
        break;
    case Tile_empty::DarkEmpty:
        image = IMG_Load("image/darktile.png");
        break;
    }
    if (image == NULL)
    {
        cerr << "Unable to load image! SDL Error: " << SDL_GetError();
    }
    else
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_RenderCopy(renderer, texture, NULL, &Tile_rect);
    }
}
void Tile::swapTile(Tile otherTile, SDL_Texture* MoveText, int speed) {
    SDL_Rect thisRect = Tile_rect;
    SDL_Rect otherRect = otherTile.Tile_rect;
    for (; otherRect.y != Tile_rect.y ;) {
        if (MoveText != NULL) {
            otherRect.y += speed;
            if (otherRect.y > Tile_rect.y) otherRect.y = Tile_rect.y;
        }
        else if (otherTile.Tile_rect.y > Tile_rect.y) {
            otherRect.y -= 7; thisRect.y += 7;
        }
        else {
            otherRect.y += 7; thisRect.y -= 7;
        }
        if (MoveText == NULL) {
            SDL_RenderCopy(renderer, texture, NULL, &thisRect);
            SDL_RenderCopy(renderer, otherTile.texture, NULL, &otherRect);
        }
        else {
            SDL_RenderCopy(renderer, MoveText, NULL, &otherRect);
        }
        SDL_RenderPresent(renderer);
        otherTile.render_empty();
        render_empty();
    }
    for (; otherRect.x != Tile_rect.x;) {
        if (otherTile.Tile_rect.x > Tile_rect.x) {
            otherRect.x -= 7; thisRect.x += 7;
        }
        else {
            otherRect.x += 7; thisRect.x -= 7;
        }
        SDL_RenderCopy(renderer, texture, NULL, &thisRect);
        SDL_RenderCopy(renderer, otherTile.texture, NULL, &otherRect);
        SDL_RenderPresent(renderer);
        otherTile.render_empty();
        render_empty();
    }
}