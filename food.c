#include "food.h"

// generate a position variable with random values
Position random_board_pos(void)
{
    Position pos = {0};
    pos.x = rand() % BOARD_WIDTH;
    pos.y = rand() % BOARD_HEIGHT;
    
    return pos;
}

// check if the generated position variable collids with an other object
int pos_is_not_empty(Game *game, Position pos)
{
    // with food
        if (pos.x == game->food.position.x && pos.y == game->food.position.y)
        {
            return 1;
        }

    // with snake body
    for (int i = 0; i < game->player_number; i++)
    {
        for (int j = 0; j < game->snake[i].length; j++)
        {
            if (pos.x == game->snake[i].body[j].x && pos.y == game->snake[i].body[j].y)
            {
                return 1;
            }
        }
    }
    
    if (game->obstacle_flag == 1)
    {
        // with obstacles
        for (int i = 0; i < OBSTACLES_COUNT; i++)
        {
            if (pos.x == game->obstacle[i].x && pos.y == game->obstacle[i].y)
            {
                return 1;
            }
        }

        // with obstacle edges
        Position edges[28] = {{1, 1}, {24, 1}, {24, 24}, {1, 24}, {2, 2}, {2, 4}, {4, 4}, {4, 2}, {21, 2}, {23, 2}, {23, 4},
                                {21, 4}, {21, 21}, {23, 21}, {23, 23}, {21, 23}, {2, 21}, {4, 21}, {4, 23}, {2, 23}, 
                                    {11, 7}, {14, 7}, {14, 10}, {11, 10}, {11, 15}, {14, 15}, {14, 18}, {11, 18}};
        for (int i = 0; i < 28; i++)
        {
            if (pos.x == edges[i].x && pos.y == edges[i].y)
            {
                return 1;
            }
        }
    }
    
    return 0;
}

// keep generating a position variable until an empty one is found
Position random_empty_board_pos(Game *game)
{
    Position pos = {0};
    do 
    {
        pos = random_board_pos();
    } while (pos_is_not_empty(game, pos) == 1);

    return pos;
}

// initializing food
void init_food(Game *game)
{
    game->food.position = random_empty_board_pos(game);

    return;
}

// check for food
Food *check_for_food(Game *game)
{
    Snake *snake0 = &game->snake[0];
    Position head_pos0 = *get_snake_head(snake0);

    Food *food = &game->food;
    // check if snake0 ate food
    if (food->position.x == head_pos0.x && food->position.y == head_pos0.y)
    {
        food->id = 0;
        return food;
    }

    if (game->player_number == 2)
    {
        Snake *snake1 = &game->snake[1];
        Position head_pos1 = *get_snake_head(snake1);

        //check if snake1 ate food
        if (food->position.x == head_pos1.x && food->position.y == head_pos1.y)
        {
            food->id = 1;
            return food;
        }
    }
    
    return NULL;
}


void eat_food(Game *game, Food *food)
{
    Snake *snake0 = &game->snake[0];

    // grow snake's body and score depending on who ate it
    if (food->id == 0)
    {
        Position new_pos0 = peak_next_pos(snake0, snake0->direction);
        snake0->length += 1;
        snake0->body[snake0->length - 1] = new_pos0;
        game->score0 += 1;
    }

    if (game->player_number == 2)
    {
        Snake *snake1 = &game->snake[1];
        if (food->id == 1)
        {
            Position new_pos1 = peak_next_pos(snake1, snake1->direction);
            snake1->length += 1;
            snake1->body[snake1->length - 1] = new_pos1;
            game->score1 += 1;
        }
    }
    

    return;
}

// rendering food
void render_food(SDL_Renderer *renderer, Game *game) 
{
    render_square(renderer, game->food.position, HEX_COLOR(FOOD_COLOR));

    return;
}
