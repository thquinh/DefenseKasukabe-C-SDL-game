#include <SDL.h>
#include <SDL_mixer.h>
#include "SDL_mixer_function.h"
#include "SDL_utils.h"
#include "GameBoard.h"

using namespace std;

void Board::render_board() {
    for (int i = 0; i < Board_col; i++) {
        for (int j = 0; j < Board_row; j++) {
            Tile_Board[j][i].render();
        }
    }
}
void Board::Find_Tile_Selected(int xmouse, int ymouse, int &move)
{
    if (!Mix_Paused(-1)) Mix_PlayChannel(-1, selected_sound, 0);
    static int count_select = 0;
    static int tempR = 0, tempC = 0;
    for (int i = 0; i < Board_row; i++) {
        for (int j = 0; j < Board_col; j++) {
            if ((xmouse <= Tile_Board[i][j].Tile_rect.x + Tile_Board[i][j].Tile_rect.w) && (xmouse >= Tile_Board[i][j].Tile_rect.x) 
                && (ymouse <= Tile_Board[i][j].Tile_rect.y + Tile_Board[i][j].Tile_rect.h) && (ymouse >= Tile_Board[i][j].Tile_rect.y))
            { 
                if (Tile_Board[i][j].status != Tile_Status::Selected && Tile_Board[i][j].status != Tile_Status::Empty && count_select <= 1) {
                    count_select++;
                    if (count_select == 1) {
                        tempR = i;
                        tempC = j;
                    }
                    Tile_Board[i][j].status = Tile_Status::Selected;                   
                    Tile_Board[i][j].render_selected();
                    if (count_select == 2) {
                        move--;
                        if (((i == tempR - 1 && j == tempC) || (i == tempR + 1 && j == tempC) ||
                            (i == tempR && j == tempC - 1) || ((i == tempR && j == tempC + 1)))) {
                            swap(Tile_Board[i][j].mark, Tile_Board[tempR][tempC].mark);
                            Tile_Board[i][j].swapTile(Tile_Board[tempR][tempC]);
                            Tile_Board[i][j].render();
                            Tile_Board[tempR][tempC].render();
                            if (!Find_Match(hidden_point)) {
                                swap(Tile_Board[i][j].mark, Tile_Board[tempR][tempC].mark);
                                if (!Mix_Paused(-1)) Mix_PlayChannel(1, reverse_sound, 0);
                                Tile_Board[tempR][tempC].swapTile(Tile_Board[i][j]);
                            }
                            Tile_Board[i][j].render();
                            Tile_Board[tempR][tempC].render();
                        }
                        else
                        {
                            Tile_Board[i][j].render();
                            Tile_Board[tempR][tempC].render();
                        }
                        count_select = 0;
                    }
                    break;
                }
                else if (Tile_Board[i][j].status == Tile_Status::Selected) {
                    Tile_Board[i][j].render();
                    count_select--;
                }
            }
        }
    }
}
bool Board::Find_Match(long &count_point){
    speed = 25;
    for (int i = 0; i < Board_row; i++)
    {
        int k = 1;
        for (int j = 0; j < Board_col - 2;) {
            if ( k < Board_col && Tile_Board[i][j].mark == Tile_Board[i][k].mark) {
                k++;
                continue;
            }
            if (k - j >= 3) {
                count_point += (k - j) * 100;
                for (int temp = j; temp < k; temp++)
                {
                    Tile_Board[i][temp].status = Tile_Status::Empty;

                    if (!Mix_Paused(-1)) {
                        Mix_Pause(1);
                        Mix_PlayChannel(1, eatable_sound, 0);
                    }
                    Tile_Board[i][temp].render_empty();
                }
                SDL_RenderPresent(renderer);
            }
            int count_type = 0;
            if (k - j >= 5) {
                speed = 65;
                int temp = Tile_Board[i][j].mark;
                for (int i = 0; i < Board_col; i++) {
                    for (int j = 0; j < Board_row; j++) {
                        if (Tile_Board[j][i].mark == temp) {
                            Tile_Board[j][i].status = Tile_Status::Empty;
                            Tile_Board[j][i].render_empty();
                            count_type++;
                        }
                    }
                }
                SDL_RenderPresent(renderer);
                count_point += count_type * 100;
            }
            j = k;
        }
    }
    for (int i = 0; i < Board_col; i++)
    {
        int k = 1;
        for (int j = 0; j < Board_row - 2;) {
            if ( k < Board_row && Tile_Board[j][i].mark == Tile_Board[k][i].mark) {
                k++;
                continue;
            }
            if (k - j >= 3) {
                count_point += (k - j) * 100;
                for (int temp = j; temp < k; temp++) {
                    Tile_Board[temp][i].status = Tile_Status::Empty;
                    if (!Mix_Paused(-1)) {
                        Mix_Pause(1);
                        Mix_PlayChannel(1, eatable_sound, 0);
                    }
                    Tile_Board[temp][i].render_empty();
                }
                SDL_RenderPresent(renderer);
            }
            int count_type = 0;
            if (k - j >= 5) {
                speed = 65;
                int temp = Tile_Board[j][i].mark;
                for (int i = 0; i < Board_col; i++) {
                    for (int j = 0; j < Board_row; j++) {
                        if (Tile_Board[j][i].mark == temp) {
                            Tile_Board[j][i].status = Tile_Status::Empty;
                            Tile_Board[j][i].render_empty();
                            count_type++;
                        }
                    }
                }
                SDL_RenderPresent(renderer);
                count_point += count_type * 100;
            }
            j = k;
        }
    }
    for (int i = 0; i < Board_row; i++)
    {
        for (int j = 0; j < Board_col; j++)
        {
            if (Tile_Board[i][j].status == Tile_Status::Empty) {
                return true;
            }
        }
    }
    return false;
}
bool Board::Check_Possible_Move(){
    Board virtual_board;
    for (int i = 0; i < Board_row; i++)
    {
        for (int j = 0; j < Board_col; j++)
        {

            virtual_board.Tile_Board[i][j].mark = Tile_Board[i][j].mark;
        }
    }
    for (int i = 0; i < Board_row; i++)
    {
        for (int j = 0; j < Board_col - 1; j++)
        {
            swap(virtual_board.Tile_Board[i][j].mark, virtual_board.Tile_Board[i][j+1].mark);
            if (virtual_board.Find_Match(hidden_point)) {
                return true;
            }
            swap(virtual_board.Tile_Board[i][j].mark, virtual_board.Tile_Board[i][j + 1].mark);
        }
    }
    for (int i = 0; i < Board_col - 1; i++)
    {
        for (int j = 0; j < Board_row; j++)
        {
            swap(virtual_board.Tile_Board[i][j].mark, virtual_board.Tile_Board[i+1][j].mark);
            if (virtual_board.Find_Match(hidden_point)) {
                return true;
            }
            swap(Tile_Board[i][j].mark, Tile_Board[i + 1][j].mark);
        }
    }
    return false;
}
void Board::Drop_Tiles(long &point){
    for (int i = 0; i < Board_col; i++)
    {
        static int k = 0;
        for (int j = Board_row - 1; j >= 0; j--)
        {
            if (Tile_Board[j][i].status == Tile_Status::Empty) {
                for (k = j - 1; k >= 0; k--) {
                    if (Tile_Board[k][i].status != Tile_Status::Empty) {
                        Tile_Board[j][i].mark = Tile_Board[k][i].mark;
                        Tile_Board[k][i].status = Tile_Status::Empty;
                        if (speed != 65) {
                            if (j - k >= 3) speed = 50;
                            else speed = 25;
                        }
                        for (int temp = k; temp < j;){
                            Tile_Board[temp][i].swapTile(Tile_Board[temp++][i], Tile_Board[k][i].texture, speed);
                        }
                        Tile_Board[j][i].render();
                        break;
                    }
                    else continue;
                }
            }
        }
        for (int j = Board_row - 1; j >= 0; j--)
        {   
            if (Tile_Board[j][i].status == Tile_Status::Empty) {
                for (k = j; k >= 0; k--) {
                    Tile_Board[0][i].mark = rand() % NumOfTile + 1;
                    Tile_Board[0][i].render();
                    if (k == 0) break;
                    Tile_Board[k][i].mark = Tile_Board[0][i].mark;
                    Tile_Board[0][i].status = Tile_Status::Empty;
                    Tile_Board[0][i].render_empty();
                    if (speed != 65) {
                        if (j - k >= 3) speed = 50;
                        else speed = 25;
                    }
                    for (int temp = 0; temp < k;) {
                        Tile_Board[temp][i].swapTile(Tile_Board[temp++][i], Tile_Board[0][i].texture, speed);
                    }
                    Tile_Board[k][i].render();
                }
            }
        }
    }
}
void Board::Mix_Tiles(){
    int virtual_board[Board_row][Board_col];
    bool check_fill[Board_row][Board_col] = { 0 };
    for (int i = 0; i < Board_row; i++)
    {
        for (int j = 0; j < Board_col; j++)
        {

            virtual_board[i][j] = Tile_Board[i][j].mark;
        }
    }
    for (int i = 0; i < Board_row; i++)
    {
        for (int j = 0; j < Board_col; j++)
        {
            int rm = rand() % Board_row, rn = rand() % Board_col;
            if (check_fill[rm][rn]) {
                j--;
                continue;
            }
            else {
                Tile_Board[rm][rn].mark = virtual_board[i][j];
                check_fill[rm][rn] = true;
            }
        }
    }
    if (!Check_Possible_Move()) Mix_Tiles();
}
void Board::Fill_board() {
    for (int i = 0; i < Board_col; i++) {
        for (int j = 0; j < Board_row; j++) {
            if ((j % 2 == 0 && i % 2 == 0) || (j % 2 == 1) && (i % 2 == 1))
                Tile_Board[j][i].colour = Tile_empty::LightEmpty;
            else Tile_Board[j][i].colour = Tile_empty::DarkEmpty;
            Tile_Board[j][i].mark = rand() % NumOfTile + 1;
            Tile_Board[j][i].Tile_rect.x = 323 + i * 70;
            Tile_Board[j][i].Tile_rect.y = 20 + j * 70;
            if (i >= 2 && Tile_Board[j][i - 2].mark == Tile_Board[j][i - 1].mark) {
                if (Tile_Board[j][i].mark == Tile_Board[j][i - 1].mark) {
                    j--;
                    continue;
                }
            }
            if (j >= 2 && Tile_Board[j - 2][i].mark == Tile_Board[j - 1][i].mark) {
                if (Tile_Board[j][i].mark == Tile_Board[j - 1][i].mark) {
                    j--;
                    continue;
                }
            }
            Tile_Board[j][i].renderer = renderer;
            Tile_Board[j][i].render();
        }
    }
}
