#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ERROR printf("\n Error! Can't create the log.\n")
#define DASH "\n______________________________________\n"

typedef struct
{
    FILE *logs;
    char player_1;
    char player_2;
    int mode;
    int start;
} Game;
Game game;

void select_player()
{
    int p;
    do
    {
        printf("\n Play as X(1) or O(2) :: 1 or 2 ? ");
        scanf("%d", &p);
    } while (p < 1 || p > 2);

    if (p == 1)
    {
        game.player_1 = 'X';
        game.player_2 = 'O';
    }
    else
    {
        game.player_1 = 'O';
        game.player_2 = 'X';
    }
}

void banner()
{
    printf("\n TIC - TAC - TOE \n%s", DASH);
    select_player();
    printf("%s\n %c: Player 1 \n %c: Player 2 or Computer \n%s", DASH, game.player_1, game.player_2, DASH);
}

char sign(int x)
{
    return (x == 0) ? ' ' : ((x == -1) ? game.player_1 : game.player_2);
}

void board(int p[9])
{
    for (int i = 0; i < 9; i += 3)
        printf("\n\t %c | %c | %c ", sign(p[i]), sign(p[i + 1]), sign(p[i + 2]));
    printf("\n");
}

void result(int r)

{
    (r != 0) ? printf("\n %c IS THE WINNER!", ((sign(r) == game.player_1) ? game.player_1 : game.player_2))
             : printf("\n DRAW!");
    if (!game.logs)
        ERROR;
    else
        (r != 0) ? fprintf(game.logs, "\n%c IS THE WINNER!", ((sign(r) == game.player_1) ? game.player_1 : game.player_2))
                 : fprintf(game.logs, "\nDRAW!");
}

int win(int p[9]){
    int chance[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (int i = 0; i < 8; i++)
        if (p[chance[i][0]] != 0 && p[chance[i][0]] == p[chance[i][1]] && p[chance[i][0]] == p[chance[i][2]])
            return p[chance[i][0]];
    return 0;
}

int minimax(int p[9], int ply){
    int position = -1, max = -1000;

    if (win(p) != 0)
        return win(p) * ply;

    for (int i = 0; i < 9; ++i)
    {
        if (p[i] == 0)
        {
            p[i] = ply;
            int score = -minimax(p, ply * -1);
            if (score > max)
            {
                max = score;
                position = i;
            }
            p[i] = 0;
        }
    }
    return (position == -1) ? 0 : max;
}

int hard_mode(int p[9])
{
    int best_move, tmp_score = -1000;
    for (int i = 0; i < 9; i++)
    {
        if (p[i] == 0)
        {
            p[i] = 1;
            int move_score = -minimax(p, -1);
            p[i] = 0;
            if (move_score > tmp_score)
            {
                best_move = i;
                tmp_score = move_score;
            }
        }
    }
    p[best_move] = 1;
    return best_move + 1;
}

int random_position(int p[9]){
    int position;
    srand(time(0));
    while (1)
    {
        position = rand() % 10;
        if (p[position - 1] == 0)
        {
            p[position - 1] = 1;
            return position;
        }
    }
}

int normal_mode(int p[9], int turn){
    (turn == 1 || turn == 3 || turn == 7) ? hard_mode(p) : random_position(p);
}

void game_menu()
{
    char opt[3][30] = {{"Computer Vs Player - Normal"},
                       {"Computer Vs Player - Hard"},
                       {"Player Vs Player"}};
    banner();
    do
    {
        printf("\n Game Modes \n");
        for (int i = 0; i < 3; i++)
            printf("\n %d. %s  ", (i + 1), opt[i]);
        printf("\n\n Select an Option : ");
        scanf("%d", &game.mode);
    } while (game.mode < 1 || game.mode > 3);

    do
    {
        printf("\n Go First or Second ? 1 or 2 : ");
        scanf("%d", &game.start);
    } while (game.start < 1 || game.start > 2);

    printf("%s\n", DASH);
    for (int i = 1; i <= 9; i += 3)
        printf("\t %d | %d | %d \n", i, (i + 1), (i + 2));
    printf("%s", DASH);

    (!game.logs) ? ERROR : fprintf(game.logs, "\nMode : %s\n", opt[game.mode - 1]);
}

void auto_move(int p[9], int mode, int turn)
{
    (!game.logs) ? ERROR : fprintf(game.logs, "\nComputer %c Moved to %d.", game.player_2, (mode == 1) ? normal_mode(p, turn) : hard_mode(p));
}

void user_move(int p[9], int ply)
{
    int position;
    while (1)
    {
        printf("\n Player %c Move : ", sign(ply));
        scanf("%d", &position);
        if (position >= 1 && position <= 9 && p[position - 1] == 0)
        {
            (ply == -1) ? (p[position - 1] = -1) : (p[position - 1] = 1);
            break;
        }
        printf("\n Position is already occupied\n or a Wrong position number.\n");
    }
    (!game.logs) ? ERROR : fprintf(game.logs, "\nPlayer %c Moved to %d.", sign(ply), position);
}

int main()
{
    int places[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    time_t t;
    time(&t);

    game.logs = fopen("log.txt", "a");
    (!game.logs) ? ERROR : fprintf(game.logs, "\n\nCreated at %s", ctime(&t));

    game_menu();
    int s = game.start - 1;

    for (int i = s; i < (9 + s) && win(places) == 0; i++)
    {
        if (i % 2 == 0)
            user_move(places, -1);
        else if (game.mode != 3)
            auto_move(places, ((game.mode == 1) ? 1 : 2), i);
        else
            user_move(places, 1);
        board(places);
    }

    result(win(places));
    (!game.logs) ? 0 : fclose(game.logs);
    return 0;
}
