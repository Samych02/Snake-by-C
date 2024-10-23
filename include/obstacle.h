#pragma once

#include <SDL_render.h>

#include "structure.h"

void initialize_obstacles(Game* game);
void render_obstacles(SDL_Renderer* renderer, const Node* obstacle_head);
