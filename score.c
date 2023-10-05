#include <stdio.h>
#include "score.h"

// updating and displaying score in the title
void update_score(SDL_Window * window, Game *game)
{
    // formatting a string variable with score value
    char str[1000];
    if (game->player_number == 1)
    {
        sprintf(str, "Player1 Score:   %d", game->score0);
    }

    if (game->player_number == 2)
    {
        sprintf(str, "Player1   Score:   %d       Player2   Score:    %d", game->score0, game->score1);
    }
    
    // updating the windows title bar with the new score value
    SDL_SetWindowTitle(window, str);

    return;
}

// reading high score from file
int read_high_score(void)
{
    // try opening the file containing the high score
    FILE *HIGH_SCORE_FILE = fopen("HIGH_SCORE", "r+");

    // creating a new one if not found
    if (HIGH_SCORE_FILE == NULL)
    {
        HIGH_SCORE_FILE = fopen("HIGH_SCORE", "w");
        fclose(HIGH_SCORE_FILE);
    }

    //reading the high score into a new variable and closing the file
    HIGH_SCORE_FILE = fopen("HIGH_SCORE", "r");
    int HIGH_SCORE;
    fscanf(HIGH_SCORE_FILE, "%i", &HIGH_SCORE);
    fclose(HIGH_SCORE_FILE);

    return HIGH_SCORE;
}

// writing new high score into file
void write_high_score(Game *game)
{
    // cleaning the high_score file content and writing the new value into it
    FILE *HIGH_SCORE_FILE = fopen("HIGH_SCORE", "w");
    fprintf(HIGH_SCORE_FILE, "%i", game->score0);
    fclose(HIGH_SCORE_FILE);

    return;
}

// printing scores and updating high scores
void print_score(Game *game)
{
    int HIGH_SCORE = read_high_score();
    if (game->player_number == 1 && game->score0 <= HIGH_SCORE)
    {
        printf("Game Over!\nYour score is: %d\n", game->score0);
    }

    else if (game->player_number == 1 && game->score0 > HIGH_SCORE)
    {
        printf("New high score!\nThe new record is: %d\n", game->score0);
        write_high_score(game);
    }

    else if (game->player_number == 2 && game->score0 <= HIGH_SCORE && game->score1 <= HIGH_SCORE)
    {
        printf("Game Over!\nPlayer1's scores is: %d\nPlayer2's score is: %d\n", game->score0, game->score1);
    }

    else if (game->player_number == 2 && (game->score0 > HIGH_SCORE || game->score1 > HIGH_SCORE))
    {
        printf("New high score!\nThe new record is: %d\nPlayer1's scores is: %d\nPlayer2's score is: %d\n", (game->score0 >= game->score1) ? game->score0 : game->score1, game->score0, game->score1);
        write_high_score(game);
    }

    return;
}
