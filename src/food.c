#include <SDL_render.h>

#include "constants.h"
#include "rendering.h"
#include "structure.h"
#include "utils.h"

void generate_random_food_position(Game* game)
{
    game->food = (Position){rand() % BOARD_LENGTH, rand() % BOARD_LENGTH};
}

bool validate_generated_food_position(const Game* game)
{
    Position food = game->food;
    // check if the generated position collides with borders or obstacles or snakes
    if (game->border_head != NULL)
    {
        const Node* border_node_tmp = game->border_head;
        while (border_node_tmp != NULL)
        {
            if (compare_position(&border_node_tmp->data.position, &food)) return false;
            border_node_tmp = border_node_tmp->next;
        }
    }

    if (game->obstacle_head != NULL)
    {
        const Node* obstacle_node_tmp = game->obstacle_head;
        while (obstacle_node_tmp != NULL)
        {
            if (compare_position(&obstacle_node_tmp->data.position, &food)) return false;
            obstacle_node_tmp = obstacle_node_tmp->next;
        }
    }

    const Node* snake_node_tmp = game->snake_head;
    while (snake_node_tmp != NULL)
    {
        if (snake_node_tmp->data.snake->id == -1)
        {
            snake_node_tmp = snake_node_tmp->next;
            continue;
        }
        const Node* snake_body_node = snake_node_tmp->data.snake->body;
        while (snake_body_node != NULL)
        {
            if (compare_position(&snake_body_node->data.position, &food)) return false;
            snake_body_node = snake_body_node->next;
        }
        snake_node_tmp = snake_node_tmp->next;
    }
    return true;
}

void generate_valid_food_position(Game* game)
{
    do
    {
        generate_random_food_position(game);
    }
    while (!validate_generated_food_position(game));
}

void initialize_food(Game* game)
{
    game->food = (Position){-1, -1};
    generate_valid_food_position(game);
}

void render_food(SDL_Renderer* renderer, const Position* food)
{
    render_square(renderer, food, (Color) FOOD_COLOR);
}
