#ifndef DUNGEON_GAME_COMMON_H
#define DUNGEON_GAME_COMMON_H

typedef struct location_t {
    int x, y;
} Location;

typedef enum direction_t {
    DIR_NONE, DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT
} Direction;

/*
 * @brief return random value within range
 * @param min minimal applicable value
 * @param max maximal applicable value
 * @return random number in given range
 */
int rand_range(int min, int max);
#endif //DUNGEON_GAME_COMMON_H
