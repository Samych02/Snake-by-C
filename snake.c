#include <sys/time.h>
#include "snake.h"
#include "rendering.h"

// getting snake head coordinates
Position *get_snake_head(Snake *snake) 
{
  return &snake->body[snake->length - 1];
}

// allowing automatic movement for both snake 0 and 1
int allow_snake_movement0(int manual, Game *game)
{
    static struct timeval old_t = {0};
    static struct timeval new_t = {0};
    static int init = -1;
    double time_elapsed = -1;

    if (init == -1)
    {
        // first and unique call to function
        init = 1;
        gettimeofday(&old_t, NULL);
        return 0;
    }
        
    gettimeofday(&new_t, NULL);
    time_elapsed = (double) (new_t.tv_usec - old_t.tv_usec) / 1000000 + (double) (new_t.tv_sec - old_t.tv_sec);
    
    if ((manual == 0) && (time_elapsed < game->speed))
    {
        // not enough time has passed for automatic movement
        return 0;
    } 

    else
    {
        old_t = new_t;
        return 1;
    }
}

int allow_snake_movement1(int manual, Game *game)
{
    static struct timeval old_t = {0};
    static struct timeval new_t = {0};
    static int init = -1;
    double time_elapsed = -1;

    if (init == -1)
    {
        // first and unique call to function
        init = 1;
        gettimeofday(&old_t, NULL);
        return 0;
    }
        
    gettimeofday(&new_t, NULL);
    time_elapsed = (double) (new_t.tv_usec - old_t.tv_usec) / 1000000 + (double) (new_t.tv_sec - old_t.tv_sec);
    
    if ((manual == 0) && (time_elapsed < game->speed))
    {
        // not enough time has passed for automatic movement
        return 0;
    } 

    else
    {
        old_t = new_t;
        return 1;
    }
}

// getting the next position of the snake before moving
Position peak_next_pos(Snake *snake, Direction dir)
{
    Position new_pos;
    Position *head_pos = get_snake_head(snake);

    switch(dir)
    {
    case RIGHT:
        new_pos.x = (head_pos->x + 1) % BOARD_WIDTH;
        new_pos.y = head_pos->y;
        break;
        
    case LEFT:
        new_pos.x = head_pos->x == 0 ? BOARD_WIDTH - 1 : head_pos->x - 1;
        new_pos.y = head_pos->y;
        break;

    case UP:
        new_pos.x = head_pos->x;    
        new_pos.y = head_pos->y == 0 ? BOARD_HEIGHT - 1 : head_pos->y - 1;
        break;

    case DOWN:
        new_pos.x = head_pos->x;    
        new_pos.y = (head_pos->y + 1) % BOARD_HEIGHT;
        break;
    }

    return new_pos;
}



// moving snake 0 and 1
void move_snake0(Game *game, Direction dir, int manual)
{
    if (allow_snake_movement0(manual, game) == 0)
    {
        return;
    }

    Snake *snake = &game->snake[0];
    Position new_pos = peak_next_pos(snake, dir);

    // perform movement
    Position *head_pos = get_snake_head(snake);
    Position old_pos = *head_pos;
    Position tmp_pos = old_pos;

    *head_pos = new_pos;
    snake->direction = dir;

    for (int i = snake->length -2 ; i >= 0; i--)
    {
        tmp_pos = snake->body[i];
        snake->body[i] = old_pos;
        old_pos = tmp_pos;
    }
}

void move_snake1(Game *game, Direction dir, int manual)
{
    if (allow_snake_movement1(manual, game) == 0)
    {
        return;
    }

    Snake *snake = &game->snake[1];
    Position new_pos = peak_next_pos(snake, dir);

    // perform movement
    Position *head_pos = get_snake_head(snake);
    Position old_pos = *head_pos;
    Position tmp_pos = old_pos;

    *head_pos = new_pos;
    snake->direction = dir;

    for (int i = snake->length -2 ; i >= 0; i--)
    {
        tmp_pos = snake->body[i];
        snake->body[i] = old_pos;
        old_pos = tmp_pos;
    }
}

// rendering snake
void render_snake(SDL_Renderer *renderer, Game *game, int id)
{
        for (int i = game->snake[id].length - 1; i >= 0; i--)
        {
            render_square(renderer, game->snake[id].body[i], HEX_COLOR(SNAKE_COLOR + ((id == 0) ? 0 : 0x238FD000)));
        }

    return;
}

// deleting snake when losing (useful in 2players mode)
void delete_snack(Game *game, int id)
{
    Snake snake = {0};
    game->snake[id] = snake;
    game->quit[id] = 1;

    return;
}
