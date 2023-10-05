
#include "game.h"

// initiating game
void init_game(Game *game)
{
    // initiating game properties
    game->score0  = 0;
    game->score1  = 0;
    game->quit[0] = 0;
    game->quit[1] = (game->player_number == 2) ? 0 : 1;
    game->quit[2] = 0;

    // initiating snake properties
    game->snake[0].length    = 2;
    game->snake[0].body[0]   = (Position){13, 12};
    game->snake[0].body[1]   = (Position){12, 12};
    game->snake[0].direction = LEFT;

    if (game->player_number == 2)
    {
        game->snake[1].length = 2;
        game->snake[1].body[0] = (Position){12, 13};
        game->snake[1].body[1] = (Position){13, 13};
        game->snake[1].direction = RIGHT;
    }

    // initiating obstacles
    if (game->obstacle_flag == 1)
    {
        init_plus_obstacle(game);
        init_wall_obstacle(game);
    }
    
    // initiating food
    init_food(game);

    return;
}

// updating game stats
void update_game_state(Game *game)
{
    // moving snakes as long as they did'nt loose
    if (game->quit[0] == 0)
    {
        move_snake0(game, game->snake[0].direction, 0);
    }

    if (game->quit[1] == 0)
    {
        move_snake1(game, game->snake[1].direction, 0);
    }

    check_for_obstacles(game);

    Food *food = check_for_food(game);

    // refresh food position when eaten
    if (food != NULL)
    {
        eat_food(game, food);
        init_food(game);
    }

    return;
}

// rendering different component of the game
void render_game(SDL_Renderer *renderer, SDL_Window * window, Game *game)
{
    sdl_check_code(SDL_SetRenderDrawColor(renderer, HEX_COLOR(BACKGROUND_COLOR)));
    SDL_RenderClear(renderer);

    render_obstacles(renderer, game);

    // rendering snake as long as they didn't lose
    if (game->quit[0] == 0)
    {
        render_snake(renderer, game, 0);
    }

    if (game->player_number == 2 && game->quit[1] == 0)
    {
        render_snake(renderer, game, 1);
    }

    render_food(renderer, game);
    update_score (window, game);
    SDL_RenderPresent(renderer);
    
    return;
}
