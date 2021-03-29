#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "SDL_utils.h"
#include "SDL_image_functions.h"
#include "SDL_mixer_function.h"
#include "SDL_ttf_function.h"
#include "GameBoard.h"

using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Defense Kasukabe!";

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    srand(time(0));
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    // Your drawing code here
    // use SDL_RenderPresent(renderer) to show it
    if (!LoadMusic()) cerr << "Failed to load music!" << endl;
    SDL_Event e;
    SDL_Rect rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    Show_image(renderer, "image/background.png", rect);
    rect = { 700, 500, 150, 80 };
    Show_image(renderer, "image/playbutton.png", rect);
    bool quit = false;
    Mix_PlayMusic(background_music, -1);
    while (!quit) {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int xmouse = e.button.x; // Lấy hoành độ x của chuột
            int ymouse = e.button.y; // Lấy tung độ y của chuột
            // Xoá toàn bộ màn hình và vẽ lại với màu sắc tuỳ thuộc chuột trái hay phải được nhấn
            bool inside = (xmouse <= 850) && (xmouse >= 700) && (ymouse <= 580) && (ymouse >= 500);
            if (e.button.button == SDL_BUTTON_LEFT && inside) {
                rect = { 700, 500, 150, 80 };
                Mix_PlayChannel( -1 , eatable_sound, 0);
                Show_image(renderer, "image/playbuttondown.png", rect);
                SDL_Delay(100);
                Board game_board(renderer);
                rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
                Show_image(renderer, "image/gameboard.png", rect);
                SDL_Rect urScore = { 110, 117, 150, 30 };
                LoadFont("00000000", renderer, urScore);
                SDL_Rect TarScore = { 110, 290, 150, 30 };
                LoadFont("99999999", renderer, TarScore);
                game_board.Fill_board();
                
            }
            else quit = false;
        }
    }
    //Khi thông thường chạy với môi trường bình thường ở nhà
    //SDL_RenderPresent(renderer);
    CloseMusic();
    CloseIMG();
    CloseFont();
    quitSDL(window, renderer);
    return 0;
}
