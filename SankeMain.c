#include "GameDataLoader.h"


int main() {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  SDL_Keycode lastKey;
  SDL_DisplayMode mode;
  float start, end;
  int condition = 1, delay = 1000 / 11, i, collided = 0;
  SDL_Rect food_instance = { -1, -1, 64, 64};
  init_game();
  load_level_data();
  load_sprite_data();
  lastKey = snake->direction;



  if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_FULLSCREEN, &window, &renderer) < 0) {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    return -1;
  }
  if  ((snake_head = IMG_LoadTexture(renderer, head_path)) == NULL || (snake_body = IMG_LoadTexture(renderer, body_path)) == NULL || (food_texture = IMG_LoadTexture(renderer, food_path)) == NULL || (background = IMG_LoadTexture(renderer, background_path)) == NULL || (snake_tail = IMG_LoadTexture(renderer, tail_path)) == NULL || (obstacle = IMG_LoadTexture(renderer, obstacle_path)) == NULL) {
    printf("Error:%s\n", IMG_GetError() );
    return -1;
  }
  while (!collided) {
    start = SDL_GetTicks();
    clear_background(renderer);
    if (SDL_PollEvent(&event) > 0) {
      switch (event.type) {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          condition = 0;
          break;
        case SDLK_LEFT:
          if (lastKey == SDLK_RIGHT || lastKey == SDLK_LEFT) {
            break;
          }
          change_direction( (-1) * texture_width, 0, head_left, SDLK_LEFT);

          break;
        case SDLK_RIGHT:
          if (lastKey == SDLK_LEFT || lastKey == SDLK_RIGHT) {
            break;
          }
          change_direction( texture_width, 0, head_right, SDLK_RIGHT);
          break;
        case SDLK_UP:
          if (lastKey == SDLK_DOWN || lastKey == SDLK_UP) {
            break;
          }
          change_direction( 0, (-1) * texture_height, head_up, SDLK_UP);
          break;
        case SDLK_DOWN:
          if (lastKey == SDLK_UP || lastKey == SDLK_DOWN ) {
            break;
          }
          change_direction( 0,  texture_height, head_down, SDLK_DOWN);
          break;
        }
        lastKey = event.key.keysym.sym;
      }
    }
    generate_food(renderer, &food_instance);
    generate_obs(renderer);
    update_texture(last);
    render_snake(renderer);
    SDL_RenderPresent(renderer);
    if (check_snake_collision(snake) == 1) {
      collided = 1;
    }
    for (i = 0; i < obstacle_length; i++) {

      if (check_collision(snake->x, snake->y, obstacles[i].x, obstacles[i].y) == 1) {
        collided = 1;
      }

    }
    if (check_collision(snake->x, snake->y, food_instance.x, food_instance.y) == 1) {
      increase_length(&snake, &snake_body, &snake_head);
      food_instance.x = -1;
    }
    end = SDL_GetTicks();
    if (end - start < delay)
      SDL_Delay(delay - end + start);
  }
  SDL_DestroyTexture( snake_head);
  SDL_DestroyTexture( snake_tail);
  SDL_DestroyTexture( snake_body );
  SDL_DestroyTexture(food_texture);
  SDL_DestroyTexture( obstacle);
  SDL_DestroyRenderer( renderer );
  SDL_DestroyWindow( window );
  IMG_Quit();
  SDL_Quit();
}
