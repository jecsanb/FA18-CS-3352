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

enum Winner {
    true = 1,
    false = 0
};
enum Draw {
    rock = 0,
    paper = 1,
    scissors = 2,
    none = 3
};
struct Player {
    char *name;
    enum Draw played;
    enum Winner won;
    enum Winner draw;
};

void play(struct Player *player) {
    player->played = rand() % 3;      // Returns a pseudo-random integer between 0 and RAND_MAX.


}

void score(struct Player *player1, struct Player *player2) {
    struct Player draw = {"play", none, false, true};
    char *hands[1][3] = {"Rock",
                         "Paper",
                         "Scissors"};

    struct Player *results[3][3] = {
            {&draw,   player2, player1},
            {player1, &draw,   player2},
            {player2, player1, &draw}
    };
    (results[player1->played][player2->played])->won = true;

    printf("Player %s: %s V.S Player %s: %s\n", player1->name, hands[0][player1->played],
           player2->name, hands[0][player2->played]);

}

int main(int argc, char **argv) {
    srand(time(NULL));   // Initialization, should only be called once.
    struct Player p1 = {"one", none, 0}, p2 = {"two", none, 0};
    while (p1.won == p2.won) {
        play(&p1);
        play(&p2);
        score(&p1, &p2);
    }
    printf("Winner is player %s\n", (p1.won ? p1.name : p2.name));
    return 0;
}