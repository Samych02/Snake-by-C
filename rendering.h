// defining rendering's functionnality
#ifndef RENDERING_H
#define RENDERING_H

// includes
#include <stdint.h>
#include "SDL2/SDL.h"
#include "structure.h"

// prototypes
void sdl_check_code(int code);
void *sdl_check_pointer(void *ptr);
void render_square(SDL_Renderer *renderer, Position pos, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

#endif // RENDERING_H
