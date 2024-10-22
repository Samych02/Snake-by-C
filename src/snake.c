#include <stdlib.h>

#include "constants.h"
#include "linked_list.h"
#include "structure.h"

Position get_snake_head_position(const Node* body)
{
    return *get_list_tail(body).position;
}

// Get a snake's futur position in x number of steps in specific direction
Position get_future_position(const Snake* snake, const int step)
{
    const Position head_position = get_snake_head_position(snake->body);
    Position future_position = {0};
    switch (snake->direction)
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

}