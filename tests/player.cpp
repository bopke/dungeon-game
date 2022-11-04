#include "gtest/gtest.h"

extern "C" {
#include "../src/player.h"
}

TEST(Players, WealthManipulation) {
    Player *player = create_player(0, Location{13, 37});
    ASSERT_TRUE(player != NULL);
    EXPECT_EQ(player->id, 0);
    EXPECT_EQ(player->location.x, 13);
    EXPECT_EQ(player->location.y, 37);
    add_wealth(player, 10);
    EXPECT_EQ(player->pocketChange, 10);
    EXPECT_EQ(player->bankAccount, 0);
    transfer_wealth_to_bank(player);
    EXPECT_EQ(player->pocketChange, 0);
    EXPECT_EQ(player->bankAccount, 10);
    add_wealth(player, 5);
    EXPECT_EQ(player->pocketChange, 5);
    EXPECT_EQ(player->bankAccount, 10);
    reset_wealth(player);
    EXPECT_EQ(player->pocketChange, 0);
    EXPECT_EQ(player->bankAccount, 10);
}
