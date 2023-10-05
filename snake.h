// Defining snake's functionnality
#ifndef SNAKE_H
#define SNAKE_H

// includes
#include "structure.h"
#include "SDL2/SDL.h"

// Prototypes
Position *get_snake_head(Snake *snake);
int allow_snake_movement0(int manual, Game *game);
int allow_snake_movement1(int manual, Game *game);
Position peak_next_pos(Snake *snake, Direction dir);
void move_snake0(Game *game, Direction dir, int manual);
void move_snake1(Game *game, Direction dir, int manual);
void render_snake(SDL_Renderer *renderer, Game *game, int id);
void delete_snack(Game *game, int id);

#endif // SNAKE_H
