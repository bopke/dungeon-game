#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * @brief allocates Map and set its fields to appropriate values
 * @param height vertical size of map
 * @param width horizontal size of map
 * @return pointer to filled Map struct, or Null if allocation failed
 */
Map *create_map(unsigned int height, unsigned int width) {
    Map *map = malloc(sizeof(Map));
    if (map == NULL)return NULL;
    map->height = height;
    map->width = width;
    map->fields = malloc(height * sizeof(*(map->fields)));
    if (map->fields == NULL) {
        free(map);
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        map->fields[i] = calloc(width, sizeof(**(map->fields)));
        if (map->fields[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(map->fields[j]);
            }
            free(map->fields);
            free(map);
            return NULL;
        }
    }
    return map;
}

/*
 * @brief Loads map fields from file
 * @param file source to read map from
 * @param map struct to be filled
 * @return 0 on success, 1 on error e.g. file ends before fields are filled
 */
int read_map(FILE *file, Map *map) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            map->fields[i][j] = fgetc(file);
            printf("%c", map->fields[i][j]);
        }
        fgetc(file); // discard newline
        printf("\n");
    }
    if (feof(file)) return 1;
    return 0;
}

/*
 * @brief validates if map contains only permissible set of field types
 * @param map struct to be validated
 * @return 0 on success, 1 on error e.g. invalid field type
 */
int validate_map(const Map *map) {
    static char permitted_field_types[] = {FLOOR, WALL, BUSH, COIN, SMALL_TREASURE, BIG_TREASURE, CAMPSITE, '\0'};
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (!strchr(permitted_field_types, map->fields[i][j])) {
                return 1;
            }
        }
    }
    return 0;
}

int load_map(const char *filename, Map **pMap) {
    FILE *file = fopen(filename, "rt");
    if (file == NULL) {
        return 1;
    }
    unsigned int height, width;
    if (fscanf(file, "%u %u\n", &height, &width) != 2 || height == 0 || width == 0) {
        fclose(file);
        return 2;
    }
    Map *map = create_map(height, width);
    if (map == NULL) {
        fclose(file);
        return -1;
    }

    if (read_map(file, map)) {
        fclose(file);
        destroy_map(&map);
        return 3;
    }

    if (validate_map(map)) {
        fclose(file);
        destroy_map(&map);
        return 4;
    }

    fclose(file);
    *pMap = map;
    return 0;
}

void destroy_map(Map **pMap) {
    Map *map = *pMap;
    for (int i = 0; i < map->height; i++) {
        free(map->fields[i]);
    }
    free(map->fields);
    free(map);
}
