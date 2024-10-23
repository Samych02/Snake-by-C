#pragma once
#include <SDL_render.h>

#include "structure.h"

void initialize_borders(Game* game);
void render_borders(SDL_Renderer* renderer, const Node* border_head);

