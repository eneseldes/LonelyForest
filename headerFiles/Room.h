#ifndef ROOM_H
#define ROOM_H

#include "Creature.h"
#include "Item.h"

#define MAX_ITEMS_IN_ROOM 5
#define MAX_DESCRIPTION 256

typedef struct
{
    char description[MAX_DESCRIPTION];
    Item *items[MAX_ITEMS_IN_ROOM];
    int itemCount;
    Creature *creature;
    int connections[4]; // up, right, down, left
} Room;

extern Room room;

#endif