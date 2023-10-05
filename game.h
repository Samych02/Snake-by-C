// defining game's functionnality
#ifndef GAME_H
#define GAME_H

// includes
#include "SDL2/SDL.h"
#include "structure.h"
#include "rendering.h"
#include "snake.h"
#include "obstacle.h"
#include "food.h"
#include "score.h"

// protypes
void init_game(Game *game);
void update_game_state(Game *game);
void render_game(SDL_Renderer *renderer, SDL_Window * window, Game *game);

#endif // SNAKE_H
