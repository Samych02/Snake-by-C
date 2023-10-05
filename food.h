// defining food's functionnality
#ifndef FOOD_H
#define FOOD_H

// includes
#include "SDL2/SDL.h"
#include "structure.h"
#include "rendering.h"
#include "snake.h"

// prototypes
Position random_board_pos(void);
int pos_is_not_empty(Game *game, Position pos);
Position random_empty_board_pos(Game *game);
void init_food(Game *game);
Food *check_for_food(Game *game);
void eat_food(Game *game, Food *Food);
void render_food(SDL_Renderer *renderer, Game *game);

#endif // FOOD_H
