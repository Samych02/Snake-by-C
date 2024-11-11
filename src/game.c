#include <SDL.h>
#include <SDL_timer.h>
#include <stdlib.h>

#include "constants.h"
#include "structure.h"
#include "utils.h"
#include "obstacle.h"
#include "border.h"
#include "food.h"
#include "linked_list.h"
#include "snake.h"
#include "score.h"

Game* initialize_game(const bool set_settings)
{
  static int player_number;
  static bool border_flag;
  static bool obstacle_flag;
  static Uint32 speed;

  // If game is initialized for the first time or if the player wants to change settings after losing
  if (set_settings)
  {
    player_number = (get_valid_input("Choose number of players: (1/2): ", "12") == '1') ? 1 : 2;
    border_flag = (get_valid_input("Add borders? (y/n): ", "yYnN") == 'y') ? true : false;
    obstacle_flag = (get_valid_input("Add obstacles? (y/n): ", "yYnN") == 'y') ? true : false;
    speed = (get_valid_input("Fast snake? (y/n): ", "yYnN") == 'y') ? 150 : 250;
  }

  Game* game = check_memory_allocation(malloc(sizeof(Game)));

  game->speed = speed;
  game->border_head = NULL;
  game->obstacle_head = NULL;
  game->snake_head = NULL;
  if (border_flag) initialize_borders(game);
  if (obstacle_flag) initialize_obstacles(game);

  initialize_food(game);

  const Color snakes_colors[2] = {SNAKE0_COLOR, SNAKE1_COLOR};

  for (int i = 0; i < player_number; i++)
  {
    initialize_snakes(game, snakes_colors[i], i);
  }

  return game;
}

void destroy_game(Game* game)
{
  free_linked_list(game->border_head);
  free_linked_list(game->obstacle_head);
  free_linked_list(game->snake_head);
  free(game);
}

void update_game_state(Game* game)
{
  move_snakes(game);
  check_for_hitting_objects(game);
}

// rendering different component of the game
void render_game(SDL_Renderer* renderer, SDL_Window* window, const Game* game)
{
  const Color background_color = BACKGROUND_COLOR;
  check_sdl_execution_by_code(
    SDL_SetRenderDrawColor(
      renderer,
      background_color.red,
      background_color.green,
      background_color.blue,
      background_color.alpha
    )
  );
  SDL_RenderClear(renderer);

  render_borders(renderer, game->border_head);
  render_obstacles(renderer, game->obstacle_head);
  render_food(renderer, &game->food);
  render_snake(renderer, game->snake_head);
  update_score(window, game);

  SDL_RenderPresent(renderer);
}

void main_game_loop(SDL_Renderer* renderer, SDL_Window* window, Game* game)
{
  while (!check_if_all_snakes_lost(game))
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        print_final_score(game);
        destroy_game(game);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(0);
      }
      if (event.type == SDL_KEYDOWN) change_snake_direction(&event, game);
    }
    render_game(renderer, window, game);
    update_game_state(game);
    SDL_Delay(game->speed);
  }
  print_final_score(game);
  destroy_game(game);
  SDL_HideWindow(window);
}
