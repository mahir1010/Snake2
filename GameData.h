#ifndef GAME_DATA_H
#define GAME_DATA_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

typedef struct Tex {
	SDL_Rect  *clipped_texture;
	SDL_Texture **target_texture;
	int x;
	int y;
	struct Tex *next;
	struct Tex *prev;
	int x_incr;
	int y_incr;
	SDL_Keycode direction;
} Texture;



const char *background_path,*head_path,*tail_path,*body_path,*food_path,*obstacle_path;
SDL_Rect *head_right;
SDL_Rect *head_up;
SDL_Rect *head_left;
SDL_Rect *head_down;
SDL_Rect *tail_right;
SDL_Rect *tail_up;
SDL_Rect *tail_down;
SDL_Rect *tail_left;
SDL_Rect *body_horizontal;
SDL_Rect *body_vertical;
SDL_Rect *body_turn_up_left;
SDL_Rect  *body_turn_right_down;
SDL_Rect *body_turn_up_right;
SDL_Rect  *body_turn_left_down;
SDL_Rect *body_turn_right_up;
SDL_Rect  *body_turn_down_left;
SDL_Rect *body_turn_down_right;
SDL_Rect  *body_turn_left_up;
SDL_Rect *food;
SDL_Rect *obs;
SDL_Texture *snake_head;
SDL_Texture *snake_tail;
SDL_Texture *snake_body;
SDL_Texture *food_texture;
SDL_Texture *obstacle;
SDL_Texture *background;
Texture *snake,*last;
SDL_Point *obstacles;
int height,width,speed,obstacle_length;


void init_game();

#endif // GAME_DATA_H
