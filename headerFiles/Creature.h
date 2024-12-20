#ifndef CREATURE_H
#define CREATURE_H


#define MAX_DESCRIPTION 256

typedef struct
{
    char name[MAX_DESCRIPTION];
    int health;
    int strength;
} Creature;



#endif