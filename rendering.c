#include "rendering.h"

// check if SDL is working
void sdl_check_code(int code) 
{
    if (code < 0)
    {
        printf("SDL error: %s\n", SDL_GetError());
        exit(1);
    }

    return;
}

// check if SDL is working
void *sdl_check_pointer(void *ptr)
{
    if (ptr == NULL)
    {
        printf("SDL error: %s\n", SDL_GetError());
        exit(1);
    }

    return ptr;
}

// rendering a rectangle (square in our case)
void render_square(SDL_Renderer *renderer, Position pos, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    sdl_check_code(SDL_SetRenderDrawColor(renderer, r, g, b, a));
    
    SDL_Rect rect = {
        (int) floorf(pos.x * CELL_WIDTH),
        (int) floorf(pos.y * CELL_HEIGHT),
        (int) floorf(CELL_WIDTH),
        (int) floorf(CELL_HEIGHT),
    };

    sdl_check_code(SDL_RenderFillRect(renderer, &rect));

    return;
}
