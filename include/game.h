#pragma once
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdbool.h>

#include "structure.h"

Game* initialize_game(const bool set_settings);
void destroy_game(Game* game);
void update_game_state(Game* game);
void render_game(SDL_Renderer* renderer, SDL_Window* window, const Game* game);
void main_game_loop(SDL_Renderer* renderer, SDL_Window* window, Game* game);
