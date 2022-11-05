#ifndef DUNGEON_GAME_COMMON_H
#define DUNGEON_GAME_COMMON_H

typedef struct location_t {
    int x, y;
} Location;

typedef enum direction_t {
    DIR_NONE = 0,
    DIR_UP = 1,
    DIR_DOWN = 2,
    DIR_LEFT = 3,
    DIR_RIGHT = 4
} Direction;

/*
 * @brief return random value within range
 * @param min minimal applicable value
 * @param max maximal applicable value
 * @return random number in given range
 */
int rand_range(int min, int max);

/*
 * @brief runs passed function with given arguments every given seconds interval
 * @param interval time in seconds to wait between function calls
 * @param func function to be called every interval seconds. If function returns truthy value, repeating will stop
 * @param funcArg arguments pointer to pass to func
 */
void repeatInIntervals(int interval, int(*func)(void *), void *funcArg);

#endif //DUNGEON_GAME_COMMON_H
