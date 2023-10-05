// defining every used constant in the program
#ifndef CONSTANT_H
#define CONSTANT_H

// max nember of obstacles' unite (square)
#define OBSTACLES_COUNT 300

// max snake lenght
#define MAX_SNAKE_LENGTH ((BOARD_WIDTH * BOARD_HEIGHT) - OBSTACLES_COUNT)

#define SNAKE_COUNT 2

// defining different colors
#define OBSTACLE_COLOR   0x2E5E8E00
#define FOOD_COLOR       0xB2333100
#define BACKGROUND_COLOR 0xFFFFFF00
#define GRID_COLOR       0xFFFFFF00
#define SNAKE_COLOR      0x28603500

// converting HEX color to RGB
#define HEX_COLOR(hex)		  \
    ((hex) >> (3 * 8)) & 0xFF,\
    ((hex) >> (2 * 8)) & 0xFF,\
    ((hex) >> (1 * 8)) & 0xFF,\
    ((hex) >> (0 * 8)) & 0xFF

// rendering values
#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 400

#define BOARD_WIDTH  26
#define BOARD_HEIGHT 26

#define CELL_WIDTH ((SCREEN_WIDTH / BOARD_WIDTH))
#define CELL_HEIGHT ((SCREEN_HEIGHT / BOARD_HEIGHT))

#endif // CONSTANT_H
