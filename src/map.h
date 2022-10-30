#ifndef DUNGEON_GAME_MAP_H
#define DUNGEON_GAME_MAP_H

typedef enum field_type_t {
    FLOOR = ' ',
    WALL = '?',
    BUSH = '#',
    COIN = 'c',
    SMALL_TREASURE = 't',
    BIG_TREASURE = 'T',
    CAMPSITE = 'A'
} FieldType;

typedef struct map_t {
    unsigned int height;
    unsigned int width;
    FieldType **fields;
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

#endif //DUNGEON_GAME_MAP_H
