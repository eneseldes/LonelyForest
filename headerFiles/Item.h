#ifndef ITEM_H
#define ITEM_H


#define MAX_DESCRIPTION 256

typedef struct
{
    char description[MAX_DESCRIPTION];
    int itemType;
    int attackPower;
    int defensePower;
    int equipped;
} Item;

#endif