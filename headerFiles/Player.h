#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"
#include "Item.h"

#define MAX_ROOMS 15
#define INVENTORY_LIMIT 7

extern Room rooms[MAX_ROOMS];

typedef struct
{
    int health;
    int attackPower;
    int defensePower;
    Item *inventory[INVENTORY_LIMIT];
    int inventoryCount;
    int currentRoom;

    Item *attackItem;
    Item *armor;
    Item *shield;
} Player;

void showMap();
void move(const char *direction);
void look();
void inventory();
void pickup(const char *item);
void equip(const char *item);
void drop(const char *item);
void checkYourself();
void attack(const char *kill);

extern Player player;

#endif

