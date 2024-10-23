#pragma once
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdbool.h>

#include "structure.h"

Game* initialize_game(const double speed, const bool border_flag, const bool obstacle_flag, const int player_number);
void destroy_game(Game* game);
void destroy_game(Game* game);
void update_game_state(Game* game);
void render_game(SDL_Renderer* renderer, SDL_Window* window, const Game* game);



