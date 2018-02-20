#include "GameUtil.h"

Texture *insert_new_texture(Texture *head, int x, int y, SDL_Rect  *clipped_texture, SDL_Texture **target_texture, int x_incr, int y_incr, SDL_Keycode direction) {
	Texture *n = (Texture*)malloc(sizeof(Texture));
	if (n == NULL) {
		printf("ERROR IN ALLOCATION");
		return NULL;
	}
	n->clipped_texture = clipped_texture;
	n->x = x;
	n->y = y;
	n->target_texture = target_texture;
	n->next = NULL;
	n->prev = NULL;
	n->x_incr = x_incr;
	n->y_incr = y_incr;
	n->direction = direction;
	if (head == NULL) {
		return n;
	}
	n->next = head;
	head->prev = n;
	return n;
}


/**
 * Checks whether the head has collided with the body
 * @param  head Pointer to head of the snake
 * @return      1 if collision occured,0 if collision didn't occur.
 */
int check_snake_collision(Texture *head) {
	Texture *temp = head->next->next;
	while (temp != NULL) {
		if (check_collision(temp->x, temp->y, head->x, head->y) == 1) {
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}
/**
 * Increases the length of the snake when it eats food.
 * @param head                pointer to the head of the sanke.
 * @param target              Points to the texture to which the target body belongs.
 * @param snake_head Contains the texture require to draw head.
 */
void increase_length(Texture **head, SDL_Texture **target, SDL_Texture **snake_head) {
	Texture *next;
	*head = insert_new_texture(*head, (*head)->x + (*head)->x_incr, (*head)->y + (*head)->y_incr, (*head)->clipped_texture, snake_head, (*head)->x_incr, (*head)->y_incr, (*head)->direction);
	next = (*head)->next;
	next->target_texture = target;
	switch (next->direction) {
	case SDLK_DOWN:
	case SDLK_UP:
		next->clipped_texture = body_vertical;
		break;
	case SDLK_RIGHT:
	case SDLK_LEFT:
		next->clipped_texture = body_horizontal;
	}
}
/**
 * Generates random coordinates for food.
 * @param renderer      target renderer.
 * @param food_texture texture required to draw the food.
 * @param food          Structure contating the coordinates of food.
 */
void generate_food(SDL_Renderer *renderer, SDL_Rect *food_instance) {
	int i, collision = 1;
	while (food_instance->x == -1 && collision) {
		food_instance->x = texture_width * (rand() % (width / texture_width));
		food_instance->y = texture_height * (rand() % (height / texture_height));
		for (i = 0; i < obstacle_length; i++) {
			if (check_collision(food_instance->x, food_instance->y, obstacles[i].x, obstacles[i].y) == 1) {
				collision = 1;
				break;
			}
			collision = 0;
		}
	}
	SDL_RenderCopy(renderer, food_texture, food, food_instance);
}
/**
 * General boundry collision detection algorithm
 * @param  x  x coordinate of object1
 * @param  y  y coordinate of object1
 * @param  x1 x coordinate of object2
 * @param  y1 y coordinate of object2
 * @return    1 if collision occurs,0 if collision doesn't occur.
 */
int check_collision(int x, int y, int x1, int y1) {

	if ((x < x1 + texture_width && x + texture_width > x1) && (y < y1 + texture_height && texture_height + y > y1)) {
		return 1;
	}
	return 0;
}

void generate_obs(SDL_Renderer *renderer) {
	SDL_Rect viewing_window = {0, 0, texture_width, texture_height};
	int i;
	for (i = 0; i < obstacle_length; i++) {
		viewing_window.x = obstacles[i].x;
		viewing_window.y = obstacles[i].y;
		SDL_RenderCopy(renderer, obstacle, obs, &viewing_window);
	}
}

void change_direction(int x_incr, int y_incr, SDL_Rect *clipped_texture, SDL_Keycode direction) {
	snake->x_incr = x_incr;
	snake->y_incr = y_incr;
	snake->clipped_texture = clipped_texture;
	snake->direction = direction;
}
void update_texture() {
	Texture *temp = last->prev;
	if ( temp->x_incr == 0 && temp->y_incr == 0) {
		switch (temp->direction) {
		case SDLK_DOWN:
			last->clipped_texture = tail_down;
			last->x_incr = 0;
			last->y_incr = texture_height;
			last->direction = SDLK_DOWN;
			last->x = temp->x;
			last->y = temp->y;
			break;
		case SDLK_RIGHT:
			last->clipped_texture = tail_right;
			last->x_incr = texture_width;
			last->y_incr = 0;
			last->direction = SDLK_RIGHT;
			last->x = temp->x;
			last->y = temp->y;
			break;
		case SDLK_UP:
			last->clipped_texture = tail_up;
			last->x_incr = 0;
			last->y_incr = -1 * texture_height;
			last->direction = SDLK_UP;
			last->x = temp->x;
			last->y = temp->y;
			break;
		case SDLK_LEFT:
			last->clipped_texture = tail_left;
			last->x_incr = -1 * texture_width;
			last->y_incr = 0;
			last->direction = SDLK_LEFT;
			last->x = temp->x;
			last->y = temp->y;
			break;
		}
	} else {
		last->x += last->x_incr;
		last->y += last->y_incr;
		if (last->x > width) {
			last->x = 0;
		}
		else if (last->x < 0) {
			last->x = width;
		}
		if (last->y > height) {
			last->y = 0;
		}
		else if (last->y < 0) {
			last->y = height;
		}
	}
	while (temp->prev->prev != NULL) {

		temp->clipped_texture = temp->prev->clipped_texture;
		temp->x = temp->prev->x;
		temp->y = temp->prev->y;
		temp->x_incr = 0;
		temp->y_incr = 0;
		temp->direction = temp->prev->direction;
		temp = temp->prev;
	}
	if (temp->direction != temp->prev->direction) {
		temp->x = temp->prev->x;
		temp->y = temp->prev->y;
		temp->x_incr = 0;
		temp->y_incr = 0;
		switch (temp->prev->direction) {
		case SDLK_LEFT:
			switch (temp->direction) {
			case SDLK_UP:
				temp->clipped_texture = body_turn_up_left;
				break;
			case SDLK_DOWN:
				temp->clipped_texture = body_turn_down_left;
				break;
			}
			break;
		case SDLK_RIGHT:
			switch (temp->direction) {
			case SDLK_UP:
				temp->clipped_texture = body_turn_up_right;
				break;
			case SDLK_DOWN:
				temp->clipped_texture = body_turn_down_right;
			}
			break;
		case SDLK_UP:
			switch (temp->direction) {
			case SDLK_LEFT:
				temp->clipped_texture = body_turn_left_up;
				break;
			case SDLK_RIGHT:
				temp->clipped_texture =  body_turn_right_up;
			}
			break;
		case SDLK_DOWN:
			switch (temp->direction) {
			case SDLK_LEFT:
				temp->clipped_texture = body_turn_left_down;
				break;
			case SDLK_RIGHT:
				temp->clipped_texture = body_turn_right_down;
			}
			break;
		}
		temp->direction = temp->prev->direction;
	} else {
		temp->x_incr = temp->prev->x_incr;
		temp->y_incr = temp->prev->y_incr;
		temp->x = temp->prev->x;
		temp->y = temp->prev->y;
		temp->direction = temp->prev->direction;
		switch (temp->prev->direction) {
		case SDLK_LEFT:
		case SDLK_RIGHT:
			temp->clipped_texture = body_horizontal;
			break;
		case SDLK_UP:
		case SDLK_DOWN:
			temp->clipped_texture = body_vertical;
			break;
		}
	}



	temp = temp->prev;
	temp->x += temp->x_incr;
	temp->y += temp->y_incr;

	if (temp->x >= width ) {
		temp->x = 0;
	}
	else if (temp->x < 0) {
		temp->x = width - texture_width;
	}
	if (temp->y >= height) {
		temp->y = 0;

	}
	else if (temp->y < 0) {
		temp->y = height - texture_height;
	}

}

void render_snake(SDL_Renderer *renderer) {
	Texture *temp = snake;
	SDL_Rect viewing_window;
	viewing_window.w = texture_width;
	viewing_window.h = texture_height;
	while (temp != NULL) {
		viewing_window.x = temp->x;
		viewing_window.y = temp->y;

		SDL_RenderCopy(renderer, *(temp->target_texture), temp->clipped_texture, &viewing_window);
		temp = temp->next;
	}
}

void clear_background(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, background, NULL, NULL);
}