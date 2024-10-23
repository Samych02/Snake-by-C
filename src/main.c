#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "SDL.h"
#include "utils.h"
#include "game.h"
#include "snake.h"
//
// Created by SAMY CHERIF on 22/10/2024.
//
int main()
{
    // Seeding random generator
    srand(time(0));

    check_sdl_execution_by_code(SDL_Init(SDL_INIT_EVERYTHING));

    SDL_Window* const window = check_sdl_execution_by_pointer(
        SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_LENGTH, SCREEN_LENGTH, 0));
    SDL_Renderer* const renderer = check_sdl_execution_by_pointer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    // initiating game
    Game* game = initialize_game(0.3, true, true, 1);
    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                destroy_game(game);
                exit(0);
            }
            if (event.type == SDL_KEYDOWN) change_snake_direction(&event, game);
        }
        update_game_state(game);
        render_game(renderer, window, game);
    }

    return 0;
}