#include "player.h"

#include <stdlib.h>

Player *create_player(unsigned int id, Location location) {
    Player *player = malloc(sizeof(Player));
    if (player == NULL)return NULL;
    player->id = id;
    player->location = location;
    player->bankAccount = 0;
    player->pocketChange = 0;
    return player;
}

void add_wealth(Player *player, unsigned int amount) {
    player->pocketChange += amount;
}

void reset_wealth(Player *player) {
    player->pocketChange = 0;
}

void transfer_wealth_to_bank(Player *player) {
    player->bankAccount += player->pocketChange;
    player->pocketChange = 0;
}

void destroy_player(Player **pPlayer) {
    free(*pPlayer);
}
