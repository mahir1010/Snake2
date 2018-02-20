#ifndef GAME_UTIL_H
#define GAME_UTIL_H

#include "GameData.h"
Texture *insert_new_texture(Texture*, int, int, SDL_Rect*, SDL_Texture**, int, int, SDL_Keycode);
int check_snake_collision(Texture *head);
void increase_length(Texture **head, SDL_Texture **target, SDL_Texture **snake_head_and_tail);
void generate_food(SDL_Renderer *renderer, SDL_Rect *);
void generate_obs(SDL_Renderer *renderer);
int check_collision(int x, int y, int x1, int y1) ;
void change_direction(int x_incr, int y_incr, SDL_Rect *clipped_texture, SDL_Keycode direction);
void update_texture();

void render_snake(SDL_Renderer *renderer);

void clear_background(SDL_Renderer *renderer) ;

#endif // GAME_UTIL_H
