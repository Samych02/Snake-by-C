#include <SDL_render.h>

#include "constants.h"
#include "structure.h"
#include "utils.h"

void render_square(SDL_Renderer* renderer, const Position* position, const Color color)
{
    check_sdl_execution_by_code(SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha));

    const int cell_size = SCREEN_LENGTH / BOARD_LENGTH;
    const SDL_Rect rect = {
        position->x * cell_size,
        position->y * cell_size,
        cell_size,
        cell_size,
    };

    check_sdl_execution_by_code(SDL_RenderFillRect(renderer, &rect));
}
