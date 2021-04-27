#ifndef NORMAL_H
#define NORMAL_H
#include "GameBoard.h"

using namespace std;

enum class Type_Button {
	play,
	easy,
	medium,
	hard,
	superhard,
	sound
};

enum class Button_Status {
	Up,
	Down
};

class Button
{	
	int x = 0, y = 0;
	int w = 0, h = 0;
public:
	SDL_Renderer* renderer = NULL;
	Button_Status status = Button_Status::Up;
	SDL_Rect Button_rect = { x, y, w, h };
	Button() {};
	Button(SDL_Renderer* _renderer, SDL_Rect rect) : renderer(_renderer), Button_rect(rect) {};
	void render(const char* button_img);
};
class Game {
	SDL_Renderer* renderer = NULL;
	SDL_Event e;
	Board game_board;
public:
	Game(SDL_Renderer* _renderer, SDL_Event _e) {
		renderer = _renderer;
		e = _e;
	}
	void initialize_Game();
	void renderGame();
	void Gameplay();
};

void test(SDL_Renderer*);

char* IntTostr(long point);
char* moveStr(int moves);

#endif // !NORMAL_H

