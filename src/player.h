#ifndef DUNGEON_GAME_PLAYER_H
#define DUNGEON_GAME_PLAYER_H

#include "common.h"

typedef struct player_t {
    unsigned int id;
    Location location;
    int slowdown_rounds;
    unsigned int pocketChange;
    unsigned int bankAccount;
} Player;


/*
 * @brief allocates Player and set its fields to appropriate values
 * @param id id of created player
 * @param location initial location of player
 * @return pointer to filled Player struct, or Null if allocation failed
 */
Player *create_player(unsigned int id, Location location);

/*
 * @brief adds amount to players pocket
 * @param player player going to earn some pocket change
 * @param amount pocket change to be added to players account
 */
void add_wealth(Player *player, unsigned int amount);

/*
 * @brief zeroes players pocket change
 * @param player player to have wealth zeroed
 */
void reset_wealth(Player *player);

/*
 * @brief transfers pocket change to bank account of given player
 * @param player player to have wealth transfered to bank
 */
void transfer_wealth_to_bank(Player *player);

/*
 * @brief frees all memory used by passed Map struct.
 * @param pPlayer pointer to struct instance to be freed.
 */
void destroy_player(Player **pPlayer);

#endif //DUNGEON_GAME_PLAYER_H
