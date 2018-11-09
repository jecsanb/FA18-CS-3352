#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <lber.h>
#include <time.h>

/**
 * Jecsan Blanco
 * 2018FA OP SYSTEMS & NETWRK (CS-3352-01)
 * Programming Assignment #06
 **/

enum Hand {
    rock = 0,
    paper = 1,
    scissors = 2,
    none = 3
};
struct Player {
    char *name;
    enum Hand played;
    int winner;
};

void draw(struct Player *player) {
    player->played = rand() % 3;      // Returns a pseudo-random integer between 0 and RAND_MAX.

    char *hands[1][4] = {"Rock", "Paper", "Scissors"};
    printf("Player %s, used %s \n", player->name, hands[0][player->played]);

}

void play(struct Player *player1, struct Player *player2) {
    player1->winner = 0;
    player2->winner = 0;
    struct Player draw = {"draw", none, 1};
    struct Player *results[3][3] = {
            {&draw,   player2, player1},
            {player1, &draw,   player2},
            {player2, player1, &draw}
    };
    (results[player1->played][player2->played])->winner = 1;

}

int main(int argc, char **argv) {
    srand(time(NULL));   // Initialization, should only be called once.
    struct Player p1 = {"p1", none, 0};
    struct Player p2 = {"p2", none, 0};
    //pthread_p1
    //pthread_p2
    while (p1.winner == p2.winner) {
        draw(&p1);
        draw(&p2);
        play(&p1, &p2);
    }
    printf("Winner is %s", (p1.winner > p2.winner ? p1.name : p2.name));
    return 0;
}