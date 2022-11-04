#include "gtest/gtest.h"

extern "C" {
#include "../src/game.h"
}

TEST(Games, GameCreation) {
    Map map = {.height=1, .width=2, .fields=NULL};
    GameState *gameState = create_game(&map);
    ASSERT_TRUE(gameState != NULL);
    EXPECT_EQ(gameState->map, &map);
    EXPECT_TRUE(gameState->connectedPlayers == 0);
    for (int i = 0; i < 4; i++) {
        EXPECT_TRUE(gameState->players[i] == NULL);
    }
}

TEST(Games, PlayerMovement) {
    Field fields[3] = {{.type=FIELD_FLOOR, .isPlayerOn=0},
                       {.type=FIELD_FLOOR, .isPlayerOn=0},
                       {.type=FIELD_WALL, .isPlayerOn=0}};
    Location startingLocation = {.x=0, .y=0};
    Field *pFields = fields;
    Map map = {.height=1, .width=3, .fields=&pFields};
    GameState *gameState = create_game(&map);
    ASSERT_TRUE(gameState != NULL);
    Player *player = spawn_player(gameState);
    ASSERT_TRUE(player != NULL);
    teleport_player(gameState, player->id, startingLocation);
    ASSERT_EQ(player->location.x, 0);
    ASSERT_EQ(player->location.y, 0);
    ASSERT_TRUE(gameState->map->fields[player->location.x][player->location.y].isPlayerOn == 1);
    ASSERT_TRUE(gameState->map->fields[player->location.x][player->location.y].playerId == player->id);
    int res = move_player(gameState, player->id, DIR_RIGHT);
    ASSERT_TRUE(res == 0);
    ASSERT_EQ(player->location.x, 0);
    ASSERT_EQ(player->location.y, 1);
    ASSERT_TRUE(gameState->map->fields[player->location.x][player->location.y - 1].isPlayerOn == 0);
    ASSERT_TRUE(gameState->map->fields[player->location.x][player->location.y].isPlayerOn == 1);
    ASSERT_TRUE(gameState->map->fields[player->location.x][player->location.y].playerId == player->id);
    res = move_player(gameState, player->id, DIR_RIGHT);
    ASSERT_TRUE(res == 1);
    ASSERT_EQ(player->location.x, 0);
    ASSERT_EQ(player->location.y, 1);
    ASSERT_TRUE(gameState->map->fields[player->location.x][player->location.y].isPlayerOn == 1);
    ASSERT_TRUE(gameState->map->fields[player->location.x][player->location.y].playerId == player->id);
}
