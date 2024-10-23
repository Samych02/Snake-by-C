#include <iso646.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>

#include "constants.h"
#include "linked_list.h"
#include "rendering.h"
#include "structure.h"
#include "utils.h"

Position get_snake_head_position(const Node* body)
{
    return get_list_tail(body).position;
}

// Get a snake's futur position in x number of steps in specific direction
Position get_future_position(const Position head_position, const Direction direction, const int step)
{
    Position future_position = {0};
    switch (direction)
    {
    // Ternaries/modulo operator mean when the snake cross the limits, he will come from the other direction
    case UP:
        future_position.x = head_position.x;
        future_position.y = head_position.y - step <= 0 ? BOARD_LENGTH - step : head_position.y - step;
        break;
    case DOWN:
        future_position.x = head_position.x;
        future_position.y = (head_position.y + step) % BOARD_LENGTH;
        break;
    case RIGHT:
        future_position.x = (head_position.x + step) % BOARD_LENGTH;
        future_position.y = head_position.y;
        break;
    case LEFT:
        future_position.x = head_position.x - step <= 0 ? BOARD_LENGTH - step : head_position.x - step;
        future_position.y = head_position.y;
        break;
    }
    return future_position;
}

void generate_random_starting_position_and_direction(Snake* snake)
{
    snake->direction = (Direction)(rand() % 4);

    NodeType data;
    data.position = (Position){rand() % BOARD_LENGTH, rand() % BOARD_LENGTH};
    snake->body = front_insert(snake->body, &data);

    const int snake_initial_length = 3;
    // We will construct the rest of the body using get_future_position with the opposite snake direction
    // to get the opposite of the current direction we are using the xor operator
    // 0xor1=1
    // 1xor1=0
    // 2xor1=3
    // 3⊕1=2
    for (int i = 1; i < snake_initial_length; i++)
    {
        const Position tmp = get_future_position(get_snake_head_position(snake->body), snake->direction xor 1, i);
        data.position = tmp;
        snake->body = front_insert(snake->body, &data);
    }
}

bool validate_generated_starting_position_and_direction(const Game* game, Snake* snake)
{
    // check if the generated position collides with borders or obstacles also check if snake is far by two blocks so he won't lose at the start
    if (game->border_head != NULL)
    {
        const Node* border_node_tmp = game->border_head;
        const Node* snake_body_node_tmp = snake->body;
        while (border_node_tmp != NULL)
        {
            while (snake_body_node_tmp != NULL)
            {
                if (
                    compare_position(&border_node_tmp->data.position, &snake_body_node_tmp->data.position)
                    // ||
                    // compare_position(border_node_tmp->data.position,
                    //                  &get_future_position(get_snake_head_position(snake->body), snake->direction, 1))
                    // ||
                    // compare_position(border_node_tmp->data.position,
                    //                  &get_future_position(get_snake_head_position(snake->body), snake->direction, 2))
                )
                {
                    snake->body = free_linked_list(snake->body);
                    return false;
                }
                snake_body_node_tmp = snake_body_node_tmp->next;
            }
            border_node_tmp = border_node_tmp->next;
        }
    }

    if (game->obstacle_head != NULL)
    {
        const Node* obstacle_node_tmp = game->obstacle_head;
        const Node* snake_body_node_tmp = snake->body;
        while (obstacle_node_tmp != NULL)
        {
            while (snake_body_node_tmp != NULL)
            {
                if (
                    compare_position(&obstacle_node_tmp->data.position, &snake_body_node_tmp->data.position)
                    // ||
                    // compare_position(obstacle_node_tmp->data.position,
                    //                  &get_future_position(get_snake_head_position(snake->body), snake->direction, 1))
                    // ||
                    // compare_position(obstacle_node_tmp->data.position,
                    //                  &get_future_position(get_snake_head_position(snake->body), snake->direction, 2))
                )
                {
                    snake->body = free_linked_list(snake->body);
                    return false;
                }
                snake_body_node_tmp = snake_body_node_tmp->next;
            }
            obstacle_node_tmp = obstacle_node_tmp->next;
        }
    }

    // Check for other snakes' bodies as well except for the first one
    if (game->snake_head == NULL) return true;
    if (game->snake_head->next == NULL) return true;

    const Node* snakes_node_tmp = game->snake_head;
    const Node* snake_body_node_tmp = snake->body;
    const Node* existing_snake_body_node_tmp = snakes_node_tmp->data.snake->body;
    while (snakes_node_tmp != NULL)
    {
        while (existing_snake_body_node_tmp != NULL)
        {
            while (snake_body_node_tmp != NULL)
            {
                if (
                    compare_position(&existing_snake_body_node_tmp->data.position, &snake_body_node_tmp->data.position)
                    // ||
                    // compare_position(existing_snake_body_node_tmp->data.position,
                    //                  &get_future_position(get_snake_head_position(snake->body), snake->direction, 1))
                    // ||
                    // compare_position(existing_snake_body_node_tmp->data.position,
                    //                  &get_future_position(get_snake_head_position(snake->body), snake->direction, 2))
                )
                {
                    snake->body = free_linked_list(snake->body);
                    return false;
                }
                snake_body_node_tmp = snake_body_node_tmp->next;
            }
            existing_snake_body_node_tmp = existing_snake_body_node_tmp->next;
        }
        snakes_node_tmp = snakes_node_tmp->next;
    }
    return true;
}

// keep generating a position variable until an empty one is found
void generate_valid_random_snake_body(const Game* game, Snake* snake)
{
    do
    {
        generate_random_starting_position_and_direction(snake);
    }
    while (!validate_generated_starting_position_and_direction(game, snake));
}

void initialize_snakes(Game* game, const Color color, const int id)
{
    Snake* snake = check_memory_allocation(malloc(sizeof(Snake)));
    snake->id = id;
    snake->color = color;
    gettimeofday(&snake->old_time, NULL);
    snake->body = NULL;
    generate_valid_random_snake_body(game, snake);

    NodeType data;
    data.snake = snake;
    game->snake_head = front_insert(game->snake_head, &data);
}


// allowing automatic movement for a snake
bool allow_snake_movement(Snake* snake, const double speed)
{
    gettimeofday(&snake->new_time, NULL);

    // Calculating delta time of secs and microseconds
    const double time_elapsed = (double)(snake->new_time.tv_sec - snake->old_time.tv_sec)
        + (double)(snake->new_time.tv_usec - snake->old_time.tv_usec) / 1000000;


    if (time_elapsed < speed) return false;

    snake->old_time = snake->new_time;
    return true;
}


// moving snakes
void move_snakes(const Game* game)
{
    const Node* snake_node_tmp = game->snake_head;
    while (snake_node_tmp != NULL)
    {
        if (snake_node_tmp->data.snake->id == -1) return;
        if (!allow_snake_movement(snake_node_tmp->data.snake, game->speed)) continue;

        // perform movement
        // moving the head first to the new position
        //getting the linked list of the body
        Node* snake_body_node_tmp = snake_node_tmp->data.snake->body;
        // saving current head position
        Position tmp_position = get_snake_head_position(snake_body_node_tmp);
        // Moving the head of snake (literally) first
        // todo i am changing the tail here
        snake_body_node_tmp->data.position = get_future_position(tmp_position, snake_node_tmp->data.snake->direction,
                                                                 1);
        // moving through the linked list
        snake_body_node_tmp = snake_body_node_tmp->next;
        while (snake_body_node_tmp != NULL)
        {
            Position tmp_tmp_position = snake_body_node_tmp->data.position;
            snake_body_node_tmp->data.position = tmp_position;
            tmp_position = tmp_tmp_position;
            snake_body_node_tmp = snake_body_node_tmp->next;
        }
        print_snake(snake_node_tmp->data.snake);
        snake_node_tmp = snake_node_tmp->next;
    }
}

// rendering snake
void render_snake(SDL_Renderer* renderer, const Node* snake_head)
{
    while (snake_head != NULL)
    {
        if (snake_head->data.snake->id == -1) continue;

        const Node* snake_body_node_tmp = snake_head->data.snake->body;
        while (snake_body_node_tmp != NULL)
        {
            render_square(renderer, &snake_body_node_tmp->data.position, snake_head->data.snake->color);
            snake_body_node_tmp = snake_body_node_tmp->next;
        }
        snake_head = snake_head->next;
    }
}

// eliminate snake when losing (useful in 2players mode)
void eliminate_snack(const Game* game, const int id)
{
    const Node* snake_node_tmp = game->snake_head;
    // the -1 for décalage
    for (int i = 0; i < id - 1; ++i)
    {
        snake_node_tmp = snake_node_tmp->next;
    }
    // having an id of -1 means the snake lost
    snake_node_tmp->data.snake->id = -1;
    snake_node_tmp->data.snake->body = free_linked_list(snake_node_tmp->data.snake->body);
}

// check hitting various objects
void check_for_hitting_objects(const Game* game)
{
    const Node* snake_node = game->snake_head;
    while (snake_node != NULL)
    {
        if (snake_node->data.snake->id == -1) continue;
        const Position snake_head_position = get_snake_head_position(snake_node->data.snake->body);
        // with borders
        const Node* border_node = game->border_head;
        while (border_node != NULL)
        {
            // -----
            // for optimization
            if (snake_node->data.snake->id == -1) break;
            // -----
            if (compare_position(&border_node->data.position, &snake_head_position))
            {
                eliminate_snack(game, snake_node->data.snake->id);
                // gonna trust gpt for not messing with the original value
                border_node = NULL;
            }
            else
            {
                border_node = border_node->next;
            }
        }

        // with obstacles
        const Node* obstacle_node = game->obstacle_head;
        while (obstacle_node != NULL)
        {
            if (snake_node->data.snake->id == -1) break;
            if (compare_position(&obstacle_node->data.position, &snake_head_position))
            {
                eliminate_snack(game, snake_node->data.snake->id);
            }
            else
            {
                obstacle_node = obstacle_node->next;
            }
        }

        // // With self and other snakes' bodies (tmp_node)
        // const Node* tmp_node = game->snake_head;
        // while (tmp_node != NULL)
        // {
        //     if (snake_node->data.snake->id == -1) break;
        //     const Node* tmp_body_node = tmp_node->data.snake->body;
        //     while (tmp_body_node != NULL)
        //     {
        //         if (compare_position(&tmp_body_node->data.position, &snake_head_position))
        //         {
        //             eliminate_snack(game, snake_node->data.snake->id);
        //         }
        //         else
        //         {
        //             tmp_body_node = tmp_body_node->next;
        //         }
        //     }
        //     tmp_node = tmp_node->next;
        // }
        snake_node = snake_node->next;
    }
}

void change_snake_direction(const SDL_Event* event, const Game* game)
{
    // cant but hardcode this one
    const Node* snake_node = game->snake_head;
    switch (event->key.keysym.scancode)
    {
    case SDL_SCANCODE_UP:
        snake_node->data.snake->direction = UP;
        break;
    case SDL_SCANCODE_DOWN:
        snake_node->data.snake->direction = DOWN;
        break;
    case SDL_SCANCODE_LEFT:
        snake_node->data.snake->direction = LEFT;
        break;
    case SDL_SCANCODE_RIGHT:
        snake_node->data.snake->direction = RIGHT;
        break;
    case SDL_SCANCODE_W:
        snake_node->next->data.snake->direction = UP;
        break;
    case SDL_SCANCODE_S:
        snake_node->next->data.snake->direction = DOWN;
        break;
    case SDL_SCANCODE_A:
        snake_node->next->data.snake->direction = LEFT;
        break;
    case SDL_SCANCODE_D:
        snake_node->next->data.snake->direction = RIGHT;
        break;
    default: break;
    }
}
