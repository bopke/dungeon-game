#ifndef DUNGEON_GAME_MAP_H
#define DUNGEON_GAME_MAP_H

#include "player.h"

typedef enum field_type_t {
    FIELD_FLOOR = ' ',
    FIELD_WALL = '?',
    FIELD_BUSH = '#',
    FIELD_COIN = 'c',
    FIELD_SMALL_TREASURE = 't',
    FIELD_BIG_TREASURE = 'T',
    FIELD_CAMPSITE = 'A'
} FieldType;

typedef struct field_t {
    FieldType type;
    unsigned isPlayerOn: 1;
    union {
        unsigned int playerId;
    };
} Field;

typedef struct map_t {
    unsigned int height;
    unsigned int width;
    Field **fields;
} Map;

/*
 * @brief loads map from given file.
 * @param filename name of file with map to be loaded.
 * @param pMap pointer to write struct pointer on success
 * @return 0 on success, 1 on file opening failure, 2 on invalid map dimensions, 3 on map reading failure, 4 on map validation failure, -1 on memory allocation failure
 */
int load_map(const char *filename, Map **pMap);

/*
 * @brief frees all memory used by passed Map struct.
 * @param pMap pointer to struct instance to be freed.
 */
void destroy_map(Map **pMap);

/*
 * @deprecated
 * @brief prints Map to stdout.
 * @param map pointer to map intended to be printed.
 */
void print_map(const Map *map);

/*
 * @brief prints Map with curses to given coordinates.
 * @param map pointer to map intended to be printed.
 * @param row row number to start printing map on
 * @param column column number to start printing map on
 */
void print_map_curses(const Map *map,int row,int column);

/*
 * @brief checks if given fieldType allows entities to walk on
 * @param fieldType type of field to be checked
 * @return 0 if untravelsable, 1 if traversable
 */
int is_traversable_field(FieldType fieldType);

/*
 * @brief checks if given field is occupied by any entity
 * @param field field to be checked
 * @return 0 if unoccupied, 1 if occupied
 */
int is_occupied_field(Field *field);

/*
 * @brief finds random location with traversable field and not occupied by any entity
 * @param map map to find field on
 * @return location of free field
 */
Location get_random_free_location(Map *map);

#endif //DUNGEON_GAME_MAP_H
