#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "constant.h"
#include "rendering.h"
#include "snake.h"
#include "game.h"
#include "food.h"
#include "obstacle.h"
#include "score.h"
#undef main

// initializing globale Game type variable
Game GAME = {0};

// main function
int main(int argc, char const *argv[])
{
    int difficulty;
    // checking and executing one of the arguments
    if (argc != 2)
    {
        printf("Usage: ./play option\nTo see available run the following command: ./play help\n");
        
        return 1;
    }
    
    else if (strcasecmp(argv[1], "0") * strcasecmp(argv[1], "1") * strcasecmp(argv[1], "2") * strcasecmp(argv[1], "3") * strcasecmp(argv[1], "4") * strcasecmp(argv[1], "5") * strcasecmp(argv[1], "6") * strcasecmp(argv[1], "7") == 0) 
    {
        difficulty = (int)(atoi(argv[1]));
    }
    
    else if (strcasecmp(argv[1], "help") == 0)
    {
        printf("To play this game run the following command: ./play option\n");
        printf("Available options: \n");
        printf("          0: slow snake, no obstacles, 1 player\n");
        printf("          1: fast snake, no obstacles, 1 player\n");
        printf("          2: slow snake, with obstacles, 1 player\n");
        printf("          3: fast snake, with obstacles, 1 player\n");
        printf("          4: slow snake, no obstacles, 2 players\n");
        printf("          5: fast snake, no obstacles, 2 players\n");
        printf("          6: slow snake, with obstacles, 2 players\n");
        printf("          7: fast snake, with obstacles, 2 players\n");
        printf("          hscore: to see the high score value\n");
        printf("          reset: to to reset the high score to 0\n");
        printf("          help: to display this help message\n");

        return 0;
    }

    else if (strcasecmp(argv[1], "hscore") == 0)
    {
        printf("The highest score is: %i\n", read_high_score());

        return 0;
    }

    else if (strcasecmp(argv[1], "reset") == 0)
    {
        FILE *HIGH_SCORE_FILE = fopen("HIGH_SCORE", "w");
        fprintf(HIGH_SCORE_FILE, "0");
        fclose(HIGH_SCORE_FILE);
        printf("The score was reseted succefully.\n");

        return 0;
    }
    
    else
    {
        printf("Usage: ./play option\nTo see available run the following command: ./play help\n");
        
        return 1;
    }

    // a correct difficulty number has been typed. Continuing the program
    // setting game settings depending on the choosen mode
    switch (difficulty)
    {
        case 0:
            GAME.speed         = 0.3;
            GAME.obstacle_flag = 0;
            GAME.player_number = 1;
            break;
        case 1:
            GAME.speed         = 0.15;
            GAME.obstacle_flag = 0;
            GAME.player_number = 1;
            break;
        case 2:
            GAME.speed         = 0.3;
            GAME.obstacle_flag = 1;
            GAME.player_number = 1;
            break;
        case 3:
            GAME.speed         = 0.15;
            GAME.obstacle_flag = 1;
            GAME.player_number = 1;
            break;
        case 4:
            GAME.speed         = 0.3;
            GAME.obstacle_flag = 0;
            GAME.player_number = 2;
            break;
        case 5:
            GAME.speed         = 0.15;
            GAME.obstacle_flag = 0;
            GAME.player_number = 2;
            break;
        case 6:
            GAME.speed         = 0.3;
            GAME.obstacle_flag = 1;
            GAME.player_number = 2;
            break;
        case 7:
            GAME.speed         = 0.15;
            GAME.obstacle_flag = 1;
            GAME.player_number = 2;
            break;
    }

    // initiating SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *const window = sdl_check_pointer(SDL_CreateWindow("", 0, 0, SCREEN_WIDTH - 10, SCREEN_HEIGHT - 10, SDL_WINDOW_SHOWN)); 
    SDL_Renderer *const renderer = sdl_check_pointer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);

    // initiating game
    init_game(&GAME);

    // game loop
    while((GAME.quit[0] == 0 || GAME.quit[1] == 0) && GAME.quit[2] == 0)
    {
        SDL_Event event;

        // event handling
        while(SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT)
            {
                GAME.quit[2] = 1;
            }

            // reading and filtering keyboard inputs
            else if (event.type == SDL_KEYDOWN)
            {
                if (GAME.quit[0] == 0)
                {
                    if (event.key.keysym.sym == SDLK_UP && (GAME.snake[0].direction == RIGHT || GAME.snake[0].direction == LEFT))
                    {
                        move_snake0(&GAME, UP, 1);
                        break;
                    }

                    if (event.key.keysym.sym == SDLK_DOWN && (GAME.snake[0].direction == RIGHT || GAME.snake[0].direction == LEFT))
                    {
                        move_snake0(&GAME, DOWN, 1);
                        break;  
                    }

                    if (event.key.keysym.sym == SDLK_LEFT && (GAME.snake[0].direction == UP || GAME.snake[0].direction == DOWN))
                    {
                        move_snake0(&GAME, LEFT, 1);
                        break;
                    }

                    if (event.key.keysym.sym == SDLK_RIGHT && (GAME.snake[0].direction == UP || GAME.snake[0].direction == DOWN))
                    {
                        move_snake0(&GAME, RIGHT, 1);
                        break;
                    }	  
                }
                
                if (GAME.quit[1] == 0)
                {
                    if (event.key.keysym.sym == SDLK_z && (GAME.snake[1].direction == RIGHT || GAME.snake[1].direction == LEFT))
                    {
                        move_snake1(&GAME, UP, 1);
                        break;
                    }

                    if (event.key.keysym.sym == SDLK_s && (GAME.snake[1].direction == RIGHT || GAME.snake[1].direction == LEFT))
                    {
                        move_snake1(&GAME, DOWN, 1);
                        break;  
                    }

                    if (event.key.keysym.sym == SDLK_q && (GAME.snake[1].direction == UP || GAME.snake[1].direction == DOWN))
                    {
                        move_snake1(&GAME, LEFT, 1);
                        break;
                    }

                    if (event.key.keysym.sym == SDLK_d && (GAME.snake[1].direction == UP || GAME.snake[1].direction == DOWN))
                    {
                        move_snake1(&GAME, RIGHT, 1);
                        break;
                    }
                }
            }
        }

        // main logic loop
        update_game_state(&GAME);

        // rendering stuff
        render_game(renderer, window, &GAME);
    }

    // printing scores
    print_score(&GAME);

    // freeing resources
    SDL_Quit();
    
    return 0;
}
