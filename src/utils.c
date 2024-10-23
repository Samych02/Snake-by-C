#include <SDL_error.h>
#include <stdbool.h>
#include <stdio.h>

#include "structure.h"
#include "linked_list.h"

void check_sdl_execution_by_code(const int code)
{
    if (code < 0)
    {
        printf("SDL error: %s\n", SDL_GetError());
        exit(1);
    }
}

void* check_sdl_execution_by_pointer(void* pointer)
{
    if (pointer == NULL)
    {
        printf("SDL error: %s\n", SDL_GetError());
        exit(1);
    }
    return pointer;
}

void* check_memory_allocation(void* pointer)
{
    if (pointer == NULL)
    {
        printf("Couldn't allocate memory\n");
        exit(1);
    }
    return pointer;
}

bool compare_position(const Position* a, const Position* b)
{
    return a->x == b->x && a->y == b->y;
}

void print_snake(const Snake* snake)
{
    const Node* tmp = snake->body;
    printf("----\n");
    printf("length: %i\n", get_list_size(snake->body));
    printf("direction: %i\n", snake->direction);

    while (tmp != NULL)
    {
        printf("x: %i | y: %i\n", tmp->data.position.x, tmp->data.position.y);
        tmp = tmp->next;
    }
    printf("----\n");
}
