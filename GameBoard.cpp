#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "GameBoard.h"

using namespace std;

void Tile::Update_status() {
    switch (mark) {
    case 1:
        status = Tile_Status::Kazama;
        break;
    case 2:
        status = Tile_Status::Bo;
        break;
    case 3:
        status = Tile_Status::Nene;
        break;
    case 4:
        status = Tile_Status::Shin;
        break;
    case 5:
        status = Tile_Status::Masao;
        break;
    default:
        status = Tile_Status::empty;
    }
}
void Tile::render() {   
    SDL_Rect Tile_rect = { x, y, w, h };
    SDL_Surface* image = NULL;
    switch (status) {
    case Tile_Status::Kazama :
        image = IMG_Load("image/kazama.png");
        break;
    case Tile_Status::Bo:
        image = IMG_Load("image/bo.png");
        break;
    case Tile_Status::Nene:
        image = IMG_Load("image/nene.png");
        break;
    case Tile_Status::Shin:
        image = IMG_Load("image/shin.png");
        break;
    case Tile_Status::Masao:
        image = IMG_Load("image/masao.png");
        break;
    }
    if (image == NULL)
    {
        cout << "Unable to load image!" << status << endl
            << "SDL Error: " << SDL_GetError();
    }
    else
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_RenderCopy(renderer, texture, NULL, &Tile_rect);
        SDL_RenderPresent(renderer);
    }
}
void Tile::render_selected() {
    SDL_Rect Tile_rect = { x, y, w, h };
    SDL_Surface* image = NULL;
    image = IMG_Load("image/select.png");
    if (image == NULL)
    {
        cout << "Unable to load image! Select :" << endl
            << "SDL Error: " << SDL_GetError();
    }
    else
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_RenderCopy(renderer, texture, NULL, &Tile_rect);
        SDL_RenderPresent(renderer);
    }
}
void Tile::render_match(Tile otherTile) {
    SDL_Rect Tile_rect = { x, y, w, h };
}

void Board::Fill_board() {
    for (int i = 0; i < Board_row; i++) {
        for (int j = 0; j < Board_col; j++) {
            Img_Board[i][j].renderer = renderer;
            Img_Board[i][j].mark = rand() % NumOfTile + 1;
            Img_Board[i][j].x = 323 + i * 70;
            Img_Board[i][j].y = 20 + j * 70;
            Img_Board[i][j].w = 70;
            Img_Board[i][j].h = 70;
            Img_Board[i][j].Update_status();
            Img_Board[i][j].render();
        }
    }
}
bool Board::Find_Match(){
    return false;
}
void Board::Drop_Tiles(){}
bool Board::Check_Possible_Move(){
    return false;
}
void Board::Mix_Tiles(){}
void Board::Render_board(){}