#pragma once
#include <sys/_types/_timeval.h>

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
    int red;
    int green;
    int blue;
    int alpha;
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
    struct timeval old_time;
    struct timeval new_time;
    Direction direction;
    // this is useful when growing a snake's body
    Position tail;
    Node* body;
    int final_score;
};

typedef struct
{
    double speed;
    Position food;
    Node* obstacle_head;
    Node* border_head;
    Node* snake_head;
} Game;
