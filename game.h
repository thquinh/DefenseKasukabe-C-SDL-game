#ifndef NORMAL_H
#define NORMAL_H
#include "GameBoard.h"

using namespace std;

enum class Button_Status {
	Up,
	Down
};

class Button
{	
	int x = 0, y = 0;
	int w = 0, h = 0;
	SDL_Texture* Up_text = NULL;
	SDL_Texture* Down_text = NULL;
public:
	SDL_Renderer* renderer = NULL;
	Button_Status status = Button_Status::Up;
	SDL_Rect Button_rect = { x, y, w, h };
	Button() {};
	Button(SDL_Renderer* _renderer, SDL_Rect rect) : renderer(_renderer), Button_rect(rect) {};
	void create_text(const char* up, const char* down);
	void render();
};
class Game {
	SDL_Renderer* renderer = NULL;
	SDL_Event e;
	Board game_board;	
	long point = 0, target_point = 0;
	int move = 0;	
	Button game_button[5];
public:
	Game(SDL_Renderer* _renderer, SDL_Event _e) {
		renderer = _renderer;
		e = _e;
	}
	void initialize_Game();
	void selectLevel();
	int Gameplay();
	int result(bool res);
};

char* IntTostr(long point);
char* moveStr(int moves);

#endif // !NORMAL_H

