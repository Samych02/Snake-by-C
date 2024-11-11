#pragma once

#include <SDL_video.h>

#include "structure.h"

void update_score(SDL_Window * window, const Game *game);
void print_final_score(const Game* game);
