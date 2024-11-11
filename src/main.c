#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "SDL.h"
#include "utils.h"
#include "game.h"
#include "score.h"
#include "snake.h"
//
// Created by SAMY CHERIF on 22/10/2024.
//

//todo: learn logging
int main()
{
  // Seeding random generator
  srand(time(0));

  printf("Welcome to Snake game.\n");

  Game* game = initialize_game(true);

  check_sdl_execution_by_code(SDL_Init(SDL_INIT_EVERYTHING));

  SDL_Window* window = check_sdl_execution_by_pointer(
    SDL_CreateWindow("Snake", 0, 0, SCREEN_LENGTH, SCREEN_LENGTH, 0));
  SDL_Renderer* renderer = check_sdl_execution_by_pointer(
    SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

  main_game_loop(renderer, window, game);

  while (1)
  {
    const char final_choice = get_valid_input("Replay? Change settings? exit? (r/c/e): ", "rRcCeE");

    switch (final_choice)
    {
    case 'r':
    case 'R':
      {
        game = initialize_game(false);
        SDL_ShowWindow(window);
        SDL_RaiseWindow(window);
        SDL_Delay(500);
        main_game_loop(renderer, window, game);
        break;
      }
    case 'c':
    case 'C':
      {
        game = initialize_game(true);
        SDL_ShowWindow(window);
        SDL_RaiseWindow(window);
        SDL_Delay(500);
        main_game_loop(renderer, window, game);
        break;
      }
    case 'e':
    case 'E':
    default:
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
      exit(0);
    }
  }
}
