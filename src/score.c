#include <SDL_video.h>

#include "linked_list.h"
#include "structure.h"
// updating and displaying score in the title
void update_score(SDL_Window * window, const Game *game)
{
    // formatting a string variable with score value
    char str[1000] = "";
    char *ptr = str;       // Pointer to track current position
    const Node* snake_head = game->snake_head;
    const int number_of_players = get_list_size(snake_head);
    for (int i = 0; i < number_of_players; ++i)
    {
        ptr += sprintf(ptr, "Player%d score: %d\t\t", i + 1, snake_head->data.snake->score);
        snake_head = snake_head->next;
    }

    // updating the windows title bar with the new score value
    SDL_SetWindowTitle(window, str);
}