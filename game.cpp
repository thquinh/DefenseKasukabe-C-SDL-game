#include <iostream>
#include <sstream>
#include "SDL_utils.h"
#include <vector>
#include "SDL_image_functions.h"
#include "SDL_mixer_function.h"
#include "SDL_ttf_function.h"
#include "GameBoard.h"
#include "game.h"

using namespace std;

const char* background_img = "image/background.png";
const char* bgSelectLevel = "image/selectLevelg.jpg";
const char* gameboard_img = "image/gameboard.png";

const char* playbutton = "image/playbutton.png";
const char* playbuttondown = "image/playbuttondown.png";
const char* easybutton = "image/easy.png";
const char* easybuttondown = "image/easyDown.png";
const char* mediumbutton = "image/medium.png";
const char* mediumbuttondown = "image/mediumDown.png";
const char* hardbutton = "image/hard.png";
const char* hardbuttondown = "image/hardDown.png";
const char* superhardbutton = "image/superhard.png";
const char* superhardbuttondown = "image/superhardDown.png";

const char* soundOnbutton = "image/soundOn.png";
const char* soundOffbutton = "image/soundOff.png";

SDL_Rect back_rect = { 0, 0, 900, 600 };
SDL_Rect urScore = { 120, 117, 120, 30 };
SDL_Rect TarScore = { 120, 290, 120, 30 };
SDL_Rect MoveRect = { 190, 362, 70, 30 };
SDL_Rect play_rect = { 700, 500, 150, 80 };

char* IntTostr(long point)
{
    char* score = new char[7];
    stringstream ss;
    ss << point;
    string str = ss.str();
    int n = str.length();
    for (int i = 0; i < 6; i++)
    {
        if (i < 6 - n) score[i] = '0';
        else score[i] = str[i + n - 6];
    }
    score[6] = '\0';
    return score;
}
char* moveStr(int moves)
{
    char* score = new char[6];
    stringstream ss;
    ss << moves;
    string str = ss.str();
    int n = str.length();
    for (int i = 0; i < 2; i++)
    {
        if (i < 2 - n) score[i] = '0';
        else score[i] = str[i + n - 2];
    }
    score[2] = '\0';
    return score;
}
void Button::render(const char* button_img)
{
    SDL_Surface* image = NULL;
    image = IMG_Load(button_img);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture, NULL, &Button_rect);
    SDL_RenderPresent(renderer);
}

void test(SDL_Renderer* renderer) {
    Show_image(renderer, bgSelectLevel, back_rect);
    SDL_Rect rectL = { 600, 170, 150, 50 };
    Show_image(renderer, easybutton, rectL);
    rectL.y += 80;
    Show_image(renderer, mediumbutton, rectL);
    rectL.y += 80;
    Show_image(renderer, hardbutton, rectL);
    rectL.y += 80;
    Show_image(renderer, superhardbutton, rectL);
    rectL = { 840, 540, 55, 55 };
    Show_image(renderer, soundOnbutton, rectL);
}

void Game::initialize_Game() {
    if (!LoadMusic()) cerr << "Failed to load music!" << endl;
    Mix_VolumeChunk(eatable_sound, 64);
    Mix_VolumeChunk(selected_sound, 128);
    Mix_VolumeMusic(32);
    Show_image(renderer, background_img, back_rect);
    Show_image(renderer, playbutton, play_rect);
    Mix_PlayMusic(background_music, -1);
    bool quit = false;
    while (!quit) {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            bool inside = (e.button.x <= 850) && (e.button.x >= 700) && (e.button.y <= 580) && (e.button.y >= 500);
            if (inside) {
                Mix_PlayChannel(-1, reverse_sound, 0);
                CreateImg(renderer, playbuttondown, play_rect);
                Button game_button[5];
                for (int i = 0; i < 4; i++) {
                    game_button[i].Button_rect.x = 600;
                    game_button[i].Button_rect.y = 170 + i * 80;
                    game_button[i].Button_rect.w = 150;
                    game_button[i].Button_rect.h = 50;
                    game_button[i].renderer = renderer;
                }
                game_button[0].render(easybutton);

                SDL_RenderPresent(renderer);
                waitUntilKeyPressed();
                Show_image(renderer, gameboard_img, back_rect);
                LoadFont("000000", renderer, urScore);
                game_board.Fill_board();
                quit = true;
            }
        }

    }
}
void Game::renderGame() {
    
}
void Game::Gameplay() {
    Board game_board(renderer);
    int move = 9;
    long point = 0, TargetPoint = (rand() % (30000 - 10000 + 1) + 10000) / 1000 * 1000;
    LoadFont(IntTostr(TargetPoint), renderer, TarScore);
    LoadFont("Moves:", renderer, MoveRect);
    MoveRect = { 265, 366, 30, 25 };
    SDL_SetRenderDrawColor(renderer, 140, 70, 0, 0);
    SDL_RenderFillRect(renderer, &MoveRect);
    LoadFont(moveStr(move), renderer, MoveRect);
    game_board.Find_Tile_Selected(e.button.x, e.button.y, move);
    while (game_board.Find_Match(point)) {
        SDL_SetRenderDrawColor(renderer, 140, 70, 0, 0);
        SDL_RenderFillRect(renderer, &MoveRect);
        LoadFont(moveStr(move), renderer, MoveRect);
        game_board.Drop_Tiles(point);
        SDL_SetRenderDrawColor(renderer, 140, 70, 0, 0);
        SDL_RenderFillRect(renderer, &urScore);
        LoadFont(IntTostr(point), renderer, urScore);
    }
    SDL_Rect rect = { 900 / 2 + 50, 600 / 2 - 50, 200, 60 };
    if (point >= TargetPoint) {
        for (int i = 150; i < 900 - 350; i += 5)
        {
            rect.x = i;
            SDL_RenderClear(renderer);
            LoadFont("You Win!", renderer, rect);
        }
    }
}