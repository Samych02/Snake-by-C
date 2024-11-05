#pragma once

#include <SDL_stdinc.h>
#include <stdbool.h>

typedef struct Node Node;
typedef struct Snake Snake;

typedef enum
{
    UP,
    DOWN,
    RIGHT,
    LEFT
} Direction;

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} Color;

typedef struct
{
    int x;
    int y;
} Position;

typedef union NodeType
{
    Position position;
    Snake* snake;
} NodeType;

// Thank you cs50 for teaching me this
struct Node
{
    NodeType data;
    Node* next;
};

// I decided to remove the length field and use a method to get the list's size to reduce the risk of error when manually incrementing
struct Snake
{
    int id;
    Color color;
    Direction direction;
    // this is used to synchronize the body movement and keys
    bool can_change_direction;
    // to trigger manual movement
    bool direction_changed;
    // this is useful when growing a snake's body
    Position tail;
    Node* body;
    int score;
};

typedef struct
{
    Uint32 speed;
    Position food;
    Node* obstacle_head;
    Node* border_head;
    Node* snake_head;
} Game;
