#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int Board_row = 8;
const int Board_col = 8;
const int NumOfTile = 5;

enum Tile_Status {
	empty = 0,
	Kazama,
	Bo,
	Nene,
	Shin,
	Masao
};

class Tile {
    
public:    
    SDL_Renderer* renderer;
    int x, y;
    int w = 70, h = 70;
    int mark;
    Tile_Status status;
    Tile(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};
    Tile() {};
    ~Tile() {};  
    void Update_status();
    void render();
    void render_selected();
    void render_match(Tile otherTile);
};
class Board {

public:   
    SDL_Renderer* renderer;
    Tile Img_Board[Board_row][Board_col];
    Board(SDL_Renderer* _renderer) : renderer(_renderer){}
    void Fill_board();
    bool Find_Match();
    void Drop_Tiles();
    bool Check_Possible_Move();
    void Mix_Tiles();    
    void Render_board();
};
#endif // !GAMEBOARD_H
