#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <ctype.h>

#include "game.h"

int simulate_walking_player(void *args) {
    GameState *gameState = (GameState *) args;
    int keyPressed = getch();
    if (tolower(keyPressed) == 'q') {
        return 1;
    }
    Direction direction = rand_range(1, 5);
    move_player(gameState, 0, direction);
    print_map_curses(gameState->map, 2, 1);
    refresh();
    return 0;
}

int main() {
    srand(time(0));
    initscr();
    noecho();
    keypad(stdscr, 1);
    timeout(50);

    Map *map;
    if (load_map("tests/assets/map_correct.map", &map) != 0) {
        endwin();
        printf("Map loading error :(");
        return 1;
    }
    GameState *gameState = create_game(map);
    spawn_player(gameState);
    printw("Press Q to quit");
    repeatInIntervals(1, simulate_walking_player, gameState);

    endwin();
    return 0;
}
