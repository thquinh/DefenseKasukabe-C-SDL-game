#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_mixer_function.h"
#include "Tile.h"

using namespace std;

const int Board_row = 8;
const int Board_col = 8;
const int NumOfTile = 5;

class Board {
    SDL_Renderer* renderer = NULL;
    long hidden_point = 0;
    int speed = 25;
public:   
    Tile Tile_Board[Board_row][Board_col];
    Board() {};
    Board(SDL_Renderer* _renderer) : renderer(_renderer){}

    void Find_Tile_Selected(int xmouse, int ymouse, int &move);
    void Fill_board();
    bool Find_Match(long &count_point);
    void Drop_Tiles(long & point);
    bool Check_Possible_Move();
    void Mix_Tiles();    
};
#endif // !GAMEBOARD_H
