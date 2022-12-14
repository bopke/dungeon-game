#include "common.h"

#include <stdlib.h>

#include <unistd.h>

int rand_range(int min, int max) {
    if (max < min) {
        int t = max;
        max = min;
        min = t;
    }
    int range = max - min;
    int rand_max_uniform_value = range * (RAND_MAX / range);
    int randomized = rand();
    while (randomized > rand_max_uniform_value) randomized = rand();
    return min + randomized % range;
}

void repeatInIntervals(int interval, int(*func)(void *), void *funcArg) {
    while (1) {
        sleep(interval);
        if (func(funcArg)) {
            break;
        }
    }
}
