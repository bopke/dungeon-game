#include "gtest/gtest.h"

extern "C" {
#include "../src/map.h"
}

TEST(Maps, CorrectMapLoad) {
    Map *map;
    int res = load_map("tests/assets/map_correct.map", &map);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(map != NULL);
    EXPECT_EQ(map->height, 3);
    EXPECT_EQ(map->width, 5);
    ASSERT_TRUE(map->fields != NULL);
    FieldType correct_fields[3][5] = {
            {FIELD_WALL,  FIELD_COIN,  FIELD_BUSH,     FIELD_COIN,  FIELD_WALL},
            {FIELD_FLOOR, FIELD_FLOOR, FIELD_CAMPSITE, FIELD_FLOOR, FIELD_FLOOR},
            {FIELD_WALL,  FIELD_COIN,  FIELD_BUSH,     FIELD_COIN,  FIELD_WALL}
    };
    for (int i = 0; i < map->height; i++) {
        ASSERT_TRUE(map->fields[i] != NULL);
        for (int j = 0; j < map->width; j++) {
            EXPECT_EQ(map->fields[i][j].type, correct_fields[i][j]);
        }
    }
    print_map(map);
    destroy_map(&map);
}

TEST(Maps, NonexistentFile) {
    Map *map = (Map *) 0xDEFEC8ED;
    int res = load_map("tests/assets/map_NO_EXIST.map", &map);
    ASSERT_EQ(res, 1);
    ASSERT_EQ(map, (Map *) 0xDEFEC8ED);
}

TEST(Maps, IncorrectHeight) {
    Map *map = (Map *) 0xDEFEC8ED;
    int res = load_map("tests/assets/map_incorrect_height.map", &map);
    ASSERT_EQ(res, 2);
    ASSERT_EQ(map, (Map *) 0xDEFEC8ED);
}

TEST(Maps, IncorrectWidth) {
    Map *map = (Map *) 0xDEFEC8ED;
    int res = load_map("tests/assets/map_incorrect_width.map", &map);
    ASSERT_EQ(res, 2);
    ASSERT_EQ(map, (Map *) 0xDEFEC8ED);
}

TEST(Maps, UnfinishedFile) {
    Map *map = (Map *) 0xDEFEC8ED;
    int res = load_map("tests/assets/map_incorrect_unfinished_file.map", &map);
    ASSERT_EQ(res, 3);
    ASSERT_EQ(map, (Map *) 0xDEFEC8ED);
}

TEST(Maps, InvalidFile) {
    Map *map = (Map *) 0xDEFEC8ED;
    int res = load_map("tests/assets/map_incorrect_invalid.map", &map);
    ASSERT_EQ(res, 4);
    ASSERT_EQ(map, (Map *) 0xDEFEC8ED);
}
