#include "game.h"

#include <stdlib.h>

/*
 * @brief translates direction into Location change values
 * @param direction direction to be translated into location
 * @return location struct with change values
 */
Location get_location_from_direction(Direction direction) {
    static Location down = {.x=1, .y=0};
    static Location up = {.x=-1, .y=0};
    static Location left = {.x=0, .y=-1};
    static Location right = {.x=0, .y=1};
    static Location none = {.x=0, .y=0};
    switch (direction) {
        case DIR_DOWN:
            return down;
        case DIR_UP:
            return up;
        case DIR_LEFT:
            return left;
        case DIR_RIGHT:
            return right;
        default:
            return none;
    }
}

/*
 * @brief finds first free playerId in context of game
 * @param gameState state of game in which we want to find first empty player id
 * @return -1 if there is no free player slots, free player id otherwise
 */
int get_empty_player_id(GameState *gameState) {
    for (int i = 0; i < 4; i++) {
        if (gameState->players[i] == NULL) {
            return i;
        }
    }
    return -1;
}

GameState *create_game(Map *map) {
    GameState *gs = malloc(sizeof(GameState));
    if (gs == NULL)return NULL;
    gs->map = map;
    gs->connectedPlayers = 0;
    for (int i = 0; i < 4; i++) {
        gs->players[i] = NULL;
    }
    return gs;
}

Player *spawn_player(GameState *gameState) {
    if (gameState->connectedPlayers == 4) {
        return NULL;
    }
    Player *player = create_player(get_empty_player_id(gameState), get_random_free_location(gameState->map));
    if (player == NULL) return NULL;
    gameState->connectedPlayers++;
    gameState->players[player->id] = player;
    gameState->map->fields[player->location.x][player->location.y].isPlayerOn = 1;
    gameState->map->fields[player->location.x][player->location.y].playerId = player->id;
    return player;
}

void teleport_player(GameState *gameState, unsigned int playerId, Location location) {
    Player *player = gameState->players[playerId];
    gameState->map->fields[player->location.x][player->location.y].isPlayerOn = 0;
    gameState->map->fields[location.x][location.y].isPlayerOn = 1;
    gameState->map->fields[location.x][location.y].playerId = playerId;
    player->location = location;
}

int move_player(GameState *gameState, unsigned int playerId, Direction direction) {
    Player *player = gameState->players[playerId];
    Location directionInfluencedLocation = get_location_from_direction(direction);
    Location newLocation = {
            .x=player->location.x + directionInfluencedLocation.x,
            .y=player->location.y + directionInfluencedLocation.y
    };
    if (newLocation.x < 0) newLocation.x = gameState->map->height - 1;
    if (newLocation.y < 0) newLocation.y = gameState->map->width - 1;
    if (newLocation.x >= gameState->map->height) newLocation.x = 0;
    if (newLocation.y >= gameState->map->width) newLocation.y = 0;
    if (is_traversable_field(gameState->map->fields[newLocation.x][newLocation.y].type)) {
        gameState->map->fields[player->location.x][player->location.y].isPlayerOn = 0;
        gameState->map->fields[newLocation.x][newLocation.y].isPlayerOn = 1;
        gameState->map->fields[newLocation.x][newLocation.y].playerId = playerId;
        player->location = newLocation;
        return 0;
    }
    return 1;

}
