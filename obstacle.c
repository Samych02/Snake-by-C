#include "obstacle.h"
#include "snake.h"
#include "rendering.h"

// initiating a global variable
int index_number = 0;

// initiating a wall
void init_wall_obstacle(Game *game)
{
    VERTICAL_WALL_OBSACLE(game, index_number, 0, 0);
    VERTICAL_WALL_OBSACLE(game, index_number, 25, 0);
    HORIZONTAL_WALL_OBSACLE(game, index_number, 0, 0);
    HORIZONTAL_WALL_OBSACLE(game, index_number, 0, 25);

    return;
}

// initiating obstacles
void init_plus_obstacle(Game *game)
{
    SMALL_PLUS_OBSTACLE(game, index_number, 3, 2);
    SMALL_PLUS_OBSTACLE(game, index_number, 22, 2);
    SMALL_PLUS_OBSTACLE(game, index_number, 3, 21);
    SMALL_PLUS_OBSTACLE(game, index_number, 22, 21);
    BIG_PLUS_OBSTACLE(game, index_number, 12, 6);
    BIG_PLUS_OBSTACLE(game, index_number, 12, 14);

    return;
}

// Function that renders obstacles
void render_obstacles(SDL_Renderer *renderer, Game *game)
{
    sdl_check_code(SDL_SetRenderDrawColor(renderer, HEX_COLOR(OBSTACLE_COLOR)));

    if ( game->obstacle_flag == 1)
    {
        for (int i = 0; i < OBSTACLES_COUNT; i++)
        {
            Position obstacle = game->obstacle[i];
            render_square(renderer, obstacle, HEX_COLOR(OBSTACLE_COLOR));
        }
    }
    
    return;
}

// check hitting various obstacles
void check_for_obstacles(Game *game)
{
    Snake *snake0 = &game->snake[0];
    Position head_pos0 = *get_snake_head(snake0);

    // check if we hit our own body
    for (int i = 0; i < snake0->length - 2; i++) 
    {
        if (snake0->body[i].x == head_pos0.x && snake0->body[i].y == head_pos0.y)
        {
            delete_snack(game, 0);
        }
    }

    // check if we hit an obstacle
    for (int i = 0; i < OBSTACLES_COUNT; i++)
    {
        Position obstacle = game->obstacle[i];
        if (obstacle.x == head_pos0.x && obstacle.y == head_pos0.y)
        {
            delete_snack(game, 0);
        }
    }

    // same checks if there are 2 snakes
    if (game->player_number == 2)
    {
        Snake *snake1 = &game->snake[1];
        Position head_pos1 = *get_snake_head(snake1);

        // check if we hit our own body
        for (int i = 0; i < snake1->length - 2; i++) 
        {
            if (head_pos1.x == snake1->body[i].x && head_pos1.y == snake1->body[i].y)
            {
                delete_snack(game, 1);
            }
        }
        
        // check if we hit an obstacle
        for (int i = 0; i < OBSTACLES_COUNT; i++)
        {
            Position obstacle = game->obstacle[i];
            if (obstacle.x == head_pos1.x && obstacle.y == head_pos1.y)
            {
                delete_snack(game, 1);
            }
        }

        // check if we hit the other snake
        for (int i = 0; i < snake0->length; i++) 
            {
                if (head_pos0.x == snake1->body[i].x && head_pos0.y == snake1->body[i].y)
                {
                    delete_snack(game, 0);
                }
            }

        for (int i = 0; i < snake1->length; i++) 
            {
                if (head_pos1.x == snake0->body[i].x && head_pos1.y == snake0->body[i].y)
                {
                    delete_snack(game, 1);
                }
            }
    }

    return;
}
