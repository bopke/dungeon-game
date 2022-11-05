#include <stdio.h>

#include "game.h"

void simulate_walking_player(void *args) {
    GameState *gameState = (GameState *) args;
    Direction direction = rand_range(1, 5);
    move_player(gameState, 0, direction);
    printf("\n%%======%%\n\n");
    print_map(gameState->map);
}

int main() {
    Map *map;
    if (load_map("tests/assets/map_correct.map", &map) != 0) {
        printf("Map loading error :(");
        return 1;
    }
    GameState *gameState = create_game(map);
    spawn_player(gameState);
    repeatInIntervals(1, simulate_walking_player, gameState);
    return 0;
}
