#include "GameData.h"
#include "time.h"

void init_game() {

	srand(time(NULL));

	head_right = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	head_up = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	head_left = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	head_down = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	tail_right = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	tail_up = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	tail_left = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	tail_down = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	body_horizontal = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	body_vertical = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	body_turn_up_left = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	body_turn_up_right = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	body_turn_right_up = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	body_turn_left_up = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	body_turn_right_down = body_turn_up_left;
	body_turn_left_down = body_turn_up_right;
	body_turn_down_left =  body_turn_right_up;
	body_turn_down_right = body_turn_left_up;
	food = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	obs = (SDL_Rect*)malloc(sizeof(SDL_Rect));


}
