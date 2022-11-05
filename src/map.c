#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

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
            map->fields[i][j].type = fgetc(file);
            map->fields[i][j].isPlayerOn = 0;
        }
        fgetc(file); // discard newline
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
    static char permitted_field_types[] = {FIELD_FLOOR, FIELD_WALL, FIELD_BUSH, FIELD_COIN, FIELD_SMALL_TREASURE,
                                           FIELD_BIG_TREASURE, FIELD_CAMPSITE, '\0'};
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (!strchr(permitted_field_types, map->fields[i][j].type)) {
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

void print_map(const Map *map) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (map->fields[i][j].isPlayerOn) {
                printf("%d", map->fields[i][j].playerId);
            } else {
                printf("%c", map->fields[i][j].type);
            }
        }
        printf("\n");
    }
}

void print_map_curses(const Map *map, int row, int column) {
    for (int i = 0; i < map->height; i++) {
        move(row+i, column);
        for (int j = 0; j < map->width; j++) {
            if (map->fields[i][j].isPlayerOn) {
                attron(A_BOLD);
                printw("%d", map->fields[i][j].playerId);
                attroff(A_BOLD);
            } else {
                printw("%c", map->fields[i][j].type);
            }
        }
    }
}

int is_traversable_field(FieldType fieldType) {
    static const char TRAVERSABLE_FIELDS[] = {
            FIELD_FLOOR,
            FIELD_BUSH,
            FIELD_COIN,
            FIELD_SMALL_TREASURE,
            FIELD_BIG_TREASURE,
            FIELD_CAMPSITE,
            '\0'
    };
    if (strchr(TRAVERSABLE_FIELDS, fieldType)) {
        return 1;
    }
    return 0;
}

int is_occupied_field(Field *field) {
    return field->isPlayerOn;
}

//TODO: Potential problems on crowded maps with lots of walls
Location get_random_free_location(Map *map) {
    Location randomLocation = {
            .x=rand_range(0, map->height),
            .y=rand_range(0, map->width)
    };
    while (!is_traversable_field(map->fields[randomLocation.x][randomLocation.y].type) &&
           is_occupied_field(&map->fields[randomLocation.x][randomLocation.y])) {
        randomLocation.x = rand_range(0, map->height);
        randomLocation.y = rand_range(0, map->width);
    }
    return randomLocation;
}
