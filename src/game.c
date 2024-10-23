#include <SDL_timer.h>
#include <stdlib.h>

#include "constants.h"
#include "structure.h"
#include "utils.h"
#include "obstacle.h"
#include "border.h"
#include "linked_list.h"
#include "snake.h"

Game* initialize_game(const double speed, const bool border_flag, const bool obstacle_flag, const int player_number)
{
    Game* game = check_memory_allocation(malloc(sizeof(Game)));
    game->speed = speed;
    game->border_head = NULL;
    game->obstacle_head = NULL;
    game->snake_head = NULL;
    initialize_borders(game);
    initialize_obstacles(game);
    initialize_snakes(game, (Color)SNAKE0_COLOR, 0);
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
    check_sdl_execution_by_code(SDL_SetRenderDrawColor(renderer, background_color.red, background_color.green,
                                                       background_color.blue,
                                                       background_color.alpha));
    SDL_RenderClear(renderer);

    render_borders(renderer, game->border_head);
    render_obstacles(renderer, game->obstacle_head);
    render_snake(renderer, game->snake_head);
    // print_snake(game->snake[0]);


    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / 60);
}
