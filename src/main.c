#include <stdlib.h>
#include <time.h>

#include "SDL.h"
#include "utils.h"
//
// Created by SAMY CHERIF on 22/10/2024.
//
int main()
{
    // Seeding random generator
    srand(time(0));

    check_sdl_execution_by_code(SDL_Init(SDL_INIT_EVERYTHING));

    return 0;
}