#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "Room.h"
#include "Player.h"

#define MAX_ROOMS 15
#define MAX_DESCRIPTION 256

void addItemToRoom(int roomCount, const char description[MAX_DESCRIPTION],
        int itemType, int attackPower, int defensePower);
void addCreatureToRoom(int roomCount, char name[MAX_DESCRIPTION], int health, int strength);
bool loginScreen(const char *command);
void handleCommand(const char *command);
void initGame();
void startGame();
void saveGame(const char *filepath);
bool loadGame(const char *filepath);
void listSavedGames();
void exitGame();
int parseDirection(const char *direction);
void clearScreen();
void help();

#endif