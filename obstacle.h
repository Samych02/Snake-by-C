// declares obstacle's functionality
#ifndef OBSTACLE_H
#define OBSTACLE_H

// includes
#include "SDL2/SDL.h"
#include "structure.h"

// defining vertical borders
#define VERTICAL_WALL_OBSACLE(game, index_number, x, y)\
    (game)->obstacle[index_number++] = (Position){x, y + 0}; \
    (game)->obstacle[index_number++] = (Position){x, y + 1}; \
    (game)->obstacle[index_number++] = (Position){x, y + 2}; \
    (game)->obstacle[index_number++] = (Position){x, y + 3}; \
    (game)->obstacle[index_number++] = (Position){x, y + 4}; \
    (game)->obstacle[index_number++] = (Position){x, y + 5}; \
    (game)->obstacle[index_number++] = (Position){x, y + 6}; \
    (game)->obstacle[index_number++] = (Position){x, y + 7}; \
    (game)->obstacle[index_number++] = (Position){x, y + 8}; \
    (game)->obstacle[index_number++] = (Position){x, y + 9}; \
    (game)->obstacle[index_number++] = (Position){x, y + 10};\
    (game)->obstacle[index_number++] = (Position){x, y + 11};\
    (game)->obstacle[index_number++] = (Position){x, y + 12};\
    (game)->obstacle[index_number++] = (Position){x, y + 13};\
    (game)->obstacle[index_number++] = (Position){x, y + 14};\
    (game)->obstacle[index_number++] = (Position){x, y + 15};\
    (game)->obstacle[index_number++] = (Position){x, y + 16};\
    (game)->obstacle[index_number++] = (Position){x, y + 17};\
    (game)->obstacle[index_number++] = (Position){x, y + 18};\
    (game)->obstacle[index_number++] = (Position){x, y + 19};\
    (game)->obstacle[index_number++] = (Position){x, y + 20};\
    (game)->obstacle[index_number++] = (Position){x, y + 21};\
    (game)->obstacle[index_number++] = (Position){x, y + 22};\
    (game)->obstacle[index_number++] = (Position){x, y + 23};\
    (game)->obstacle[index_number++] = (Position){x, y + 24};\
    (game)->obstacle[index_number++] = (Position){x, y + 25};

// defining horizontal borders
#define HORIZONTAL_WALL_OBSACLE(game, index_number, x, y)	 \
    (game)->obstacle[index_number++] = (Position){x + 1, y}; \
    (game)->obstacle[index_number++] = (Position){x + 2, y}; \
    (game)->obstacle[index_number++] = (Position){x + 3, y}; \
    (game)->obstacle[index_number++] = (Position){x + 4, y}; \
    (game)->obstacle[index_number++] = (Position){x + 5, y}; \
    (game)->obstacle[index_number++] = (Position){x + 6, y}; \
    (game)->obstacle[index_number++] = (Position){x + 7, y}; \
    (game)->obstacle[index_number++] = (Position){x + 8, y}; \
    (game)->obstacle[index_number++] = (Position){x + 9, y}; \
    (game)->obstacle[index_number++] = (Position){x + 10, y};\
    (game)->obstacle[index_number++] = (Position){x + 11, y};\
    (game)->obstacle[index_number++] = (Position){x + 12, y};\
    (game)->obstacle[index_number++] = (Position){x + 13, y};\
    (game)->obstacle[index_number++] = (Position){x + 14, y};\
    (game)->obstacle[index_number++] = (Position){x + 15, y};\
    (game)->obstacle[index_number++] = (Position){x + 16, y};\
    (game)->obstacle[index_number++] = (Position){x + 17, y};\
    (game)->obstacle[index_number++] = (Position){x + 18, y};\
    (game)->obstacle[index_number++] = (Position){x + 19, y};\
    (game)->obstacle[index_number++] = (Position){x + 20, y};\
    (game)->obstacle[index_number++] = (Position){x + 21, y};\
    (game)->obstacle[index_number++] = (Position){x + 22, y};\
    (game)->obstacle[index_number++] = (Position){x + 23, y};\
    (game)->obstacle[index_number++] = (Position){x + 24, y};

// defining small plus obstacle
#define SMALL_PLUS_OBSTACLE(game, index_number, x, y)		    \
    (game)->obstacle[index_number++] = (Position){x, y};        \
    (game)->obstacle[index_number++] = (Position){x - 1, y + 1};\
    (game)->obstacle[index_number++] = (Position){x, y + 1};    \
    (game)->obstacle[index_number++] = (Position){x + 1, y + 1};\
    (game)->obstacle[index_number++] = (Position){x, y + 2}; 

// defining big plus obstacle
#define BIG_PLUS_OBSTACLE(game, index_number, x, y)				\
    (game)->obstacle[index_number++] = (Position){x, y};        \
    (game)->obstacle[index_number++] = (Position){x + 1, y};    \
    (game)->obstacle[index_number++] = (Position){x, y + 1};    \
    (game)->obstacle[index_number++] = (Position){x + 1, y + 1};\
    (game)->obstacle[index_number++] = (Position){x - 2, y + 2};\
    (game)->obstacle[index_number++] = (Position){x - 1, y + 2};\
    (game)->obstacle[index_number++] = (Position){x, y + 2};    \
    (game)->obstacle[index_number++] = (Position){x + 1, y + 2};\
    (game)->obstacle[index_number++] = (Position){x + 2, y + 2};\
    (game)->obstacle[index_number++] = (Position){x + 3, y + 2};\
    (game)->obstacle[index_number++] = (Position){x - 2, y + 3};\
    (game)->obstacle[index_number++] = (Position){x - 1, y + 3};\
    (game)->obstacle[index_number++] = (Position){x, y + 3};    \
    (game)->obstacle[index_number++] = (Position){x + 1, y + 3};\
    (game)->obstacle[index_number++] = (Position){x + 2, y + 3};\
    (game)->obstacle[index_number++] = (Position){x + 3, y + 3};\
    (game)->obstacle[index_number++] = (Position){x, y + 4};    \
    (game)->obstacle[index_number++] = (Position){x + 1, y + 4};\
    (game)->obstacle[index_number++] = (Position){x, y + 5};    \
    (game)->obstacle[index_number++] = (Position){x + 1, y + 5};

// prototypes
void init_wall_obstacle(Game *game);
void init_plus_obstacle(Game *game);
void check_for_obstacles(Game *game);
void render_obstacles(SDL_Renderer *renderer, Game *game);

#endif // OBSTACLE_H
