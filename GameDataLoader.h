#ifndef GAME_DATA_READER_H
#define GAME_DATA_READER_H
#include "libconfig.h"
#include "GameUtil.h"
#include <string.h>

int load_level_data();
int load_sprite_data();
void set_sdl_rect(SDL_Rect**,config_setting_t *);
SDL_Rect *get_clipping_window(const char *);
SDL_Texture **get_game_texture(char);
SDL_Keycode get_direction(char);
int get_x_sign(char);
int get_y_sign(char);

#endif // GAME_DATA_READER_H
