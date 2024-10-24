#include <SDL_render.h>

#include "constants.h"
#include "linked_list.h"
#include "rendering.h"
#include "structure.h"

Node* add_borders(Node* border_head)
{
    NodeType data;
    data.snake = NULL;

    for (int i = 0; i < BOARD_LENGTH; ++i)
    {
        // populating the vertical border on the left side
        data.position = (Position){0, i};
        border_head = front_insert(border_head, &data);

        // populating the vertical border on the right side
        data.position = (Position){BOARD_LENGTH - 1, i};
        border_head = front_insert(border_head, &data);
    }

    // the ±1 because the first square of the horizontal border is already populated by the vertical border...
    for (int i = 0 + 1; i < BOARD_LENGTH - 1; ++i)
    {
        // populating the horizontal border on the top side
        data.position = (Position){i, 0};
        border_head = front_insert(border_head, &data);

        // populating the horizontal border on the bottom side
        data.position = (Position){i, BOARD_LENGTH - 1};
        border_head = front_insert(border_head, &data);
    }

    return border_head;
}

void initialize_borders(Game* game)
{
    Node* border_head = NULL;
    border_head = add_borders(border_head);
    game->border_head = border_head;
}

void render_borders(SDL_Renderer* renderer, const Node* border_head)
{
    while (border_head != NULL)
    {
        render_square(renderer, &border_head->data.position, (Color) BORDER_COLOR);
        border_head = border_head->next;
    }
}
