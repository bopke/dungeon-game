#ifndef DUNGEON_GAME_GAME_H
#define DUNGEON_GAME_GAME_H

#include "player.h"
#include "map.h"

typedef struct game_state_t {
    Map *map;
    unsigned int connectedPlayers;
    Player *players[4];
} GameState;

/*
 * @brief allocates GameState and set its fields to appropriate values
 * @param map map struct to be used by game
 * @return pointer to filled GameState struct, or Null if allocation failed
 */
GameState *create_game(Map *map);

/*
 * @brief Creates new player struct and spawns him randomly on map
 * @param gameState state of game in which context we want to create new player
 * @return pointer to initiated Player, or NULL if game is full or memory allocation failure happened
 */
Player *spawn_player(GameState *gameState);

/*
 * @brief teleports player to given location. Does not check if it's valid field!
 * @param gameState state of game in which context we want to teleport said player
 * @param player id of player to be moved
 * @param location location to which we want to teleport player
 */
void teleport_player(GameState *gameState, unsigned int playerId, Location location);

/*
 * @brief moves player in given direction
 * @param gameState state of game in which context we want to move said player
 * @param playerId id of player to be moved
 * @param direction direction in which we want to move player, if possible
 * @return 0 on succesful movement, 1 on incorrect move (players location isn't changed)
 */
int move_player(GameState *gameState, unsigned int playerId, Direction direction);

/*
 * @brief teleports player to given location. Does not check if it's valid field!
 * @param gameState state of game in which context we want to teleport said player
 * @param player id of player to be moved
 * @param location location to which we want to teleport player
 */
void teleport_player(GameState *gameState, unsigned int playerId, Location location);

#endif //DUNGEON_GAME_GAME_H
