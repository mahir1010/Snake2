#include "GameDataLoader.h"


void print_error() {
	printf("Error While reading LevelDetails.cfg");
}

int load_level_data() {
	const char *type, *direction;
	int x, y, itr, len;
	config_t level_data;
	config_setting_t *dat, *child;



	config_init(&level_data);
	if (! config_read_file(&level_data, "LevelDetails.cfg")) {
		print_error();
		config_destroy(&level_data);
		return -1;

	}
	if (!config_lookup_string(&level_data, "background", &background_path)) {
		print_error();
		config_destroy(&level_data);
		return -1;
	}

	dat = config_lookup(&level_data, "snake.tail");
	if (dat == NULL) {
		print_error();
		return -1;
	}
	config_setting_lookup_string(dat, "type", &type);
	config_setting_lookup_int(dat, "x", &x);
	config_setting_lookup_int(dat, "y", &y);
	snake = insert_new_texture(snake, x, y, get_clipping_window(type), get_game_texture(type[0]), 64 * get_x_sign(type[1]), 64 * get_y_sign(type[1]), get_direction(type[1]));
	last = snake;
	dat = config_lookup(&level_data, "snake.body");
	if (dat == NULL) {
		print_error();
		return -1;
	}
	len = config_setting_length(dat);
	for (itr = 0; itr < len; itr++) {
		child = config_setting_get_elem(dat, itr);
		config_setting_lookup_string(child, "type", &type);
		config_setting_lookup_string(child, "direction", &direction);
		config_setting_lookup_int(child, "x", &x);
		config_setting_lookup_int(child, "y", &y);
		snake = insert_new_texture(snake, x, y, get_clipping_window(type), get_game_texture(type[0]), 64 * get_x_sign(direction[0]), 64 * get_y_sign(direction[0]), get_direction(direction[0]));
	}

	dat = config_lookup(&level_data, "snake.head");
	if (dat == NULL) {
		print_error();
		return -1;
	}
	config_setting_lookup_string(dat, "type", &type);
	config_setting_lookup_int(dat, "x", &x);
	config_setting_lookup_int(dat, "y", &y);
	snake = insert_new_texture(snake, x, y, get_clipping_window(type), get_game_texture(type[0]), 64 * get_x_sign(type[1]), 64 * get_y_sign(type[1]), get_direction(type[1]));

	dat = config_lookup(&level_data, "obstacle");
	len = config_setting_length(dat);
	obstacle_length = len;
	if (len > 0) {

		obstacles = (SDL_Point*)malloc(sizeof(SDL_Point) * len);
		for (itr = 0; itr < len; itr++) {
			child = config_setting_get_elem(dat, itr);
			obstacles[itr].x = config_setting_get_int_elem(child, 0);
			obstacles[itr].y = config_setting_get_int_elem(child, 1);
		}
	}
	return 1;
}

int load_sprite_data() {
	config_t sprite_data;
	config_setting_t *dat;
	config_init(&sprite_data);
	if (! config_read_file(&sprite_data, "SpriteDetails.cfg")) {
		print_error();
		config_destroy(&sprite_data);
		return -1;

	}
	config_lookup_string(&sprite_data, "head.path", &head_path);
	config_lookup_string(&sprite_data, "tail.path", &tail_path);
	config_lookup_string(&sprite_data, "body.path", &body_path);
	config_lookup_string(&sprite_data, "food.path", &food_path);
	config_lookup_string(&sprite_data, "obstacle.path", &obstacle_path);
	if ( head_path == NULL ||
	        tail_path == NULL ||
	        body_path == NULL ||
	        food_path == NULL ||
	        obstacle_path == NULL
	   ) {
		printf("Path not Specified\n" );
		return -1;
	}
	dat = config_lookup(&sprite_data, "head.up");
	set_sdl_rect(&head_up, dat);
	dat = config_lookup(&sprite_data, "head.left");
	set_sdl_rect(&head_left, dat);
	dat = config_lookup(&sprite_data, "head.right");
	set_sdl_rect(&head_right, dat);
	dat = config_lookup(&sprite_data, "head.down");
	set_sdl_rect(&head_down, dat);

	dat = config_lookup(&sprite_data, "tail.up");
	set_sdl_rect(&tail_up, dat);
	dat = config_lookup(&sprite_data, "tail.left");
	set_sdl_rect(&tail_left, dat);
	dat = config_lookup(&sprite_data, "tail.right");
	set_sdl_rect(&tail_right, dat);
	dat = config_lookup(&sprite_data, "tail.down");
	set_sdl_rect(&tail_down, dat);

	dat = config_lookup(&sprite_data, "body.vertical");
	set_sdl_rect(&body_vertical, dat);
	dat = config_lookup(&sprite_data, "body.horizontal");
	set_sdl_rect(&body_horizontal, dat);
	dat = config_lookup(&sprite_data, "body.upleft");
	set_sdl_rect(&body_turn_up_left, dat);
	dat = config_lookup(&sprite_data, "body.upright");
	set_sdl_rect(&body_turn_up_right, dat);
	dat = config_lookup(&sprite_data, "body.rightup");
	set_sdl_rect(&body_turn_right_up, dat);
	dat = config_lookup(&sprite_data, "body.leftup");
	set_sdl_rect(&body_turn_left_up, dat);

	dat = config_lookup(&sprite_data, "food.object");
	set_sdl_rect(&food, dat);

	dat = config_lookup(&sprite_data, "obstacle.object");
	set_sdl_rect(&obs, dat);


}

void set_sdl_rect(SDL_Rect **target_rect, config_setting_t *dat) {
	(*target_rect)->x = config_setting_get_int_elem(dat, 0);
	(*target_rect)->y = config_setting_get_int_elem(dat, 1);
	(*target_rect)->w = config_setting_get_int_elem(dat, 2);
	(*target_rect)->h = config_setting_get_int_elem(dat, 3);

}

SDL_Rect *get_clipping_window(const char *v) {
	if (!strcmp(v, "hd"))
		return head_down;
	else if (!strcmp(v, "td"))
		return tail_down;
	else if (!strcmp(v, "hl"))
		return head_left;
	else if (!strcmp(v, "tl"))
		return tail_left;
	else if (!strcmp(v, "hr"))
		return head_right;
	else if (!strcmp(v, "tr"))
		return tail_right;
	else if (!strcmp(v, "hu"))
		return head_up;
	else if (!strcmp(v, "tu"))
		return tail_up;
	else if (!strcmp(v, "bv")){
		printf("Return body vertical\n");
		exit(0);
		return body_vertical;
	}
	else if (!strcmp(v, "bh"))
		return body_horizontal;
	else if (!strcmp(v, "ld") || !strcmp(v, "ur"))
		return body_turn_up_right;
	else if (!strcmp(v, "rd") || !strcmp(v, "ul"))
		return body_turn_up_left;
	else if (!strcmp(v, "lu") || !strcmp(v, "dr"))
		return body_turn_down_right;
	else if (!strcmp(v, "ru") || !strcmp(v, "dl"))
		return body_turn_down_left;

}


SDL_Texture **get_game_texture(char v) {
	switch (v) {
	case 'h':
		return &snake_head;
	case 't':
		return &snake_tail;
	default:
		return &snake_body;
	}
}

SDL_Keycode get_direction(char c) {
	switch (c) {
	case 'd':
		return SDLK_DOWN;
	case 'u':
		return SDLK_UP;
	case 'l':
		return SDLK_LEFT;
	default:
		return SDLK_RIGHT;
	}
}

int get_x_sign(char c) {

	switch (c) {
	case 'r':
		return 1;
	case 'l':
		return -1;
	default:
		return 0;
	}
}

int get_y_sign(char c) {


	switch (c) {
	case 'd':
		return 1;
	case 'u':
		return -1;
	default:
		return 0;
	}
}