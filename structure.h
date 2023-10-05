// Defining every used structure in the program

#ifndef STRUCTURE_H
#define STRUCTURE_H

// includes
#include "constant.h"

// Structures
typedef enum {
    RIGHT = 0,
    UP    = 1,
    LEFT  = 2,
    DOWN  = 3,
} Direction;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position position;
    int id;
} Food;


typedef struct {
    Position body[MAX_SNAKE_LENGTH];
    int length;
    Direction direction;
} Snake;

typedef struct {
    Snake snake[2];
    Food food;
    Position obstacle[OBSTACLES_COUNT];
    double speed;
    int player_number;
    int obstacle_flag;
    int score0;
    int score1;
    int quit[3];
} Game;

#endif // STRUCTURE_H
