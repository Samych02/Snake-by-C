#pragma once

#include <SDL_events.h>
#include <SDL_render.h>

#include "structure.h"

//FILO
void change_snake_direction(const SDL_Event* event, const Game* game);
void check_for_hitting_objects(const Game* game);
void render_snake(SDL_Renderer* renderer,const Node* snake_head);
void move_snakes(const Game* game);
Node* initialize_snakes(Game* game, const Color color, const int id);
void change_snake_direction(const SDL_Event* event, const Game* game);

