// Defining main's functionnality
#ifndef SCORE_H
#define SCORE_H

// includes
#include "structure.h"
#include "SDL2/SDL.h"

//prototypes
void update_score(SDL_Window * window, Game *game);
int read_high_score(void);
void write_high_score(Game *game);
void print_score(Game *game);

#endif // SNAKE_H
