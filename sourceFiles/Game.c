//============= MAP OF THE FOREST =============//
// A = 10, B = 11, C = 12, D = 13, N = 14(FINISH)

//         4---5
//         |
//         3           D---F
//         |           |
// 0---1---2---6---A---B
//             |       |
//             7       C
//             |
//             8---9

#include <windows.h>
#include "../headerFiles/Game.h"

#define MAX_ROOMS 15
#define MAX_DESCRIPTION 256

// Game variables
Room rooms[MAX_ROOMS];
Player player;

// Functions to add item and creature to a room
void addItemToRoom(int roomCount, const char description[MAX_DESCRIPTION],
                   int itemType, int attackPower, int defensePower)
{
    rooms[roomCount].items[rooms[roomCount].itemCount] = malloc(sizeof(Item));
    strcpy(rooms[roomCount].items[rooms[roomCount].itemCount]->description, description);
    rooms[roomCount].items[rooms[roomCount].itemCount]->itemType = itemType;
    rooms[roomCount].items[rooms[roomCount].itemCount]->attackPower = attackPower;
    rooms[roomCount].items[rooms[roomCount].itemCount]->defensePower = defensePower;
    rooms[roomCount].itemCount++;
}

void addCreatureToRoom(int roomCount, char name[MAX_DESCRIPTION], int health, int strength)
{
    rooms[roomCount].creature = malloc(sizeof(Creature));
    strcpy(rooms[roomCount].creature->name, name);
    rooms[roomCount].creature->health = health;
    rooms[roomCount].creature->strength = strength;
}

//================||| LOGINSCREEN |||================//
/* User can only start, load or exit the game while on the login screen */
/*
    It returns bool. Because according to the return value, user will be
    quit from the loginscreen and head to the in-game menu.

    Return false in case you don't want to head to the in-game menu after
    execution.
*/
bool loginScreen(const char *command)
{
    char action[32], argument[64];
    int args = sscanf(command, "%31s %63[^\n]", action, argument);

    if (strcmp(action, "start") == 0)
    {
        startGame();
        printf("%s", rooms[0].description);
        return true;
    }
    else if (strcmp(action, "load") == 0 && args == 2)
    {
        if (loadGame(argument))
        {
            look();
            return true;
        }

        return false;
    }
    else if (strcmp(action, "list") == 0)
    {
        listSavedGames();
        return false;
    }
    else if (strcmp(action, "clean") == 0)
    {
        clearScreen();
        return false;
    }
    else if (strcmp(action, "exit") == 0)
        exitGame();
    else if (strcmp(action, "help") == 0)
    {
        help();
        return false;
    }
    else
    {
        printf("Invalid command. Try again.\n");
        return false;
    }

    return true;
}

//================||| HANDLECOMMAND |||================//
/* The function which will control in-game actions */
void handleCommand(const char *command)
{
    char action[32], argument[64];
    int args = sscanf(command, "%31s %63[^\n]", action, argument);

    if (strcmp(action, "move") == 0 && args == 2)
        move(argument);
    else if (strcmp(action, "look") == 0)
        look();
    else if (strcmp(action, "me") == 0)
        checkYourself();
    else if (strcmp(action, "inventory") == 0)
        inventory();
    else if (strcmp(action, "pickup") == 0 && args == 2)
        pickup(argument);
    else if (strcmp(action, "drop") == 0 && args == 2)
        drop(argument);
    else if (strcmp(action, "equip") == 0 && args == 2)
        equip(argument);
    else if (strcmp(action, "attack") == 0 && args == 2)
        attack(argument);
    else if (strcmp(action, "attack") == 0)
        attack(argument);
    else if (strcmp(action, "map") == 0)
        showMap();
    else if (strcmp(action, "save") == 0 && args == 2)
        saveGame(argument);
    else if (strcmp(action, "load") == 0 && args == 2)
    {
        // Load and look
        loadGame(argument);
        look();
    }
    else if (strcmp(action, "list") == 0)
        listSavedGames();
    else if (strcmp(action, "clean") == 0)
        clearScreen();
    else if (strcmp(action, "exit") == 0)
    {
        // Save and exit
        saveGame("autosave");
        exitGame();
    }
    else if (strcmp(action, "help") == 0)
        help();
    else
    {
        printf("Invalid command. Try again.\n");
    }
}

//================||| INITGAME |||================//
/*
    initGame is to prepare the game attributes which are
    not going to change: Path connections and descriptions
*/
void initGame()
{
    int roomCount = 0;

    // Initizalize rooms with default values
    for (int i = 0; i < MAX_ROOMS; i++)
    {
        rooms[i].itemCount = 0;
        rooms[i].creature = NULL;
        for (int j = 0; j < 4; j++)
        {
            // Set the closed road directions to -1
            rooms[i].connections[j] = -1;
        }
    }

    //========== INITIALIZE PATHS ==========//
    //========> PATH 0
    // Directions
    strcpy(rooms[roomCount].description, "You can smell the evil in the air. Find a way out from this place!\n");
    rooms[roomCount].connections[1] = 1;

    roomCount++;

    //========> PATH 1
    // Directions
    rooms[roomCount].connections[3] = 0;
    rooms[roomCount].connections[1] = 2;

    roomCount++;

    //========> PATH 2
    // Directions
    strcpy(rooms[roomCount].description, "You're at a fork in the path. The main path continues to the right, but it looks like you might find something useful if you go upstream.\n");
    rooms[roomCount].connections[0] = 3;
    rooms[roomCount].connections[1] = 6;
    rooms[roomCount].connections[3] = 1;

    roomCount++;

    //========> PATH 3
    // Directions
    strcpy(rooms[roomCount].description, "There are screams coming from far away...\n");
    rooms[roomCount].connections[0] = 4;
    rooms[roomCount].connections[2] = 2;

    roomCount++;

    //========> PATH 4
    // Directions
    strcpy(rooms[roomCount].description, "The stench of blood is all around...\n");
    rooms[roomCount].connections[1] = 5;
    rooms[roomCount].connections[2] = 3;

    roomCount++;

    //========> PATH 5
    // Directions
    strcpy(rooms[roomCount].description, "You found an abandoned house. The place looks dangerous, but useful things can be found.\n");
    rooms[roomCount].connections[3] = 4;

    roomCount++;

    //========> PATH 6
    // Directions
    strcpy(rooms[roomCount].description, "You're at a fork in the path again. The main path continues to the right.\n");
    rooms[roomCount].connections[1] = 10;
    rooms[roomCount].connections[2] = 7;
    rooms[roomCount].connections[3] = 2;

    roomCount++;

    //========> PATH 7
    // Directions
    rooms[roomCount].connections[0] = 6;
    rooms[roomCount].connections[2] = 8;

    roomCount++;

    //========> PATH 8
    // Directions
    strcpy(rooms[roomCount].description, "The stench of blood is all around...\n");
    rooms[roomCount].connections[0] = 7;
    rooms[roomCount].connections[1] = 9;

    roomCount++;

    //========> PATH 9
    // Directions
    strcpy(rooms[roomCount].description, "You found a body of a soldier slaughtered by monsters. His equipments might be useful.\n");
    rooms[roomCount].connections[3] = 8;

    roomCount++;

    //========> PATH 10 (A)
    // Directions
    strcpy(rooms[roomCount].description, "You hear an ear-shattering roar.\n");
    rooms[roomCount].connections[1] = 11;
    rooms[roomCount].connections[3] = 6;

    roomCount++;

    //========> PATH 11 (B)
    // Directions
    strcpy(rooms[roomCount].description, "Something... Furious... Nearby!...\n");
    rooms[roomCount].connections[0] = 13;
    rooms[roomCount].connections[2] = 12;
    rooms[roomCount].connections[3] = 10;

    roomCount++;

    //========> PATH 12 (C)
    // Directions
    rooms[roomCount].connections[0] = 11;

    roomCount++;

    //========> PATH 13 (D)
    // Directions
    strcpy(rooms[roomCount].description, "Once you step into, there is no come back. Last chance!..\n");
    rooms[roomCount].connections[1] = 14;
    rooms[roomCount].connections[2] = 11;

    roomCount++;

    //========> PATH 14 (FINISH)
    strcpy(rooms[roomCount].description, "A DRAGON!!!\n");
}

//================||| STARTGAME |||================//
/*
    This method initializes the game with default values.
    It is called when the game start from beginning, not
    with load files.

    Player and rooms are initialized here.
*/
void startGame()
{
    int roomCount = 0;
    char itemToAdd[MAX_DESCRIPTION] = "";
    char creatureToAdd[MAX_DESCRIPTION] = "";

    // Initialize player
    player.health = 150;
    player.attackPower = 5;
    player.defensePower = 0;
    player.inventoryCount = 0;
    player.currentRoom = 0;
    player.attackItem = malloc(sizeof(Item));
    strcpy(player.attackItem->description, "Handfist");
    player.attackItem->itemType = 1;
    player.attackItem->attackPower = 5;
    player.attackItem->defensePower = 0;
    player.attackItem->equipped = 1;
    player.armor = malloc(sizeof(Item));
    strcpy(player.armor->description, "Shirt");
    player.armor->itemType = 2;
    player.armor->attackPower = 0;
    player.armor->defensePower = 0;
    player.armor->equipped = 1;
    player.shield = malloc(sizeof(Item));
    strcpy(player.shield->description, "Drape");
    player.shield->itemType = 3;
    player.shield->attackPower = 0;
    player.shield->defensePower = 0;
    player.shield->equipped = 1;

    //============= INITIALIZE PATHS =============//
    //========> PATH 0
    // Directions
    rooms[roomCount].connections[1] = 1;

    roomCount++;

    //========> PATH 1
    // Items
    strcpy(itemToAdd, "WoodenStick");
    addItemToRoom(roomCount, itemToAdd, 1, 9, 2);

    // Creature
    strcpy(creatureToAdd, "InjuredWolf");
    addCreatureToRoom(roomCount, creatureToAdd, 15, 2);

    roomCount++;

    //========> PATH 2
    // Items
    strcpy(itemToAdd, "LargeTreeBark");
    addItemToRoom(roomCount, itemToAdd, 3, 1, 4);

    // Creature
    strcpy(creatureToAdd, "Wolf");
    addCreatureToRoom(roomCount, creatureToAdd, 50, 12);

    roomCount++;

    //========> PATH 3
    // Items
    strcpy(itemToAdd, "Axe");
    addItemToRoom(roomCount, itemToAdd, 1, 25, 5);

    roomCount++;

    //========> PATH 4
    // Creature
    strcpy(creatureToAdd, "Wolf");
    addCreatureToRoom(roomCount, creatureToAdd, 50, 12);

    roomCount++;

    //========> PATH 5
    // Items
    strcpy(itemToAdd, "Map");
    addItemToRoom(roomCount, itemToAdd, 5, 0, 0);

    strcpy(itemToAdd, "Elixir");
    addItemToRoom(roomCount, itemToAdd, 4, 0, 30);

    roomCount++;

    //========> PATH 6
    roomCount++;

    //========> PATH 7
    // Creature
    strcpy(creatureToAdd, "AlphaWolf");
    addCreatureToRoom(roomCount, creatureToAdd, 70, 14);

    roomCount++;

    //========> PATH 8
    // Creature
    strcpy(creatureToAdd, "InjuredWolf");
    addCreatureToRoom(roomCount, creatureToAdd, 15, 2);

    roomCount++;

    //========> PATH 9
    // Items
    strcpy(itemToAdd, "SoldierArmor");
    addItemToRoom(roomCount, itemToAdd, 2, 1, 14);

    strcpy(itemToAdd, "SoldierShield");
    addItemToRoom(roomCount, itemToAdd, 3, 1, 9);

    // Creature
    strcpy(creatureToAdd, "Werewolf");
    addCreatureToRoom(roomCount, creatureToAdd, 90, 18);

    roomCount++;

    //========> PATH 10 (A)
    // Items
    strcpy(itemToAdd, "WoodenShield");
    addItemToRoom(roomCount, itemToAdd, 3, 1, 6);

    roomCount++;

    //========> PATH 11 (B)
    // Items
    strcpy(itemToAdd, "SwordOfSteel");
    addItemToRoom(roomCount, itemToAdd, 1, 31, 4);

    strcpy(itemToAdd, "BigElixir");
    addItemToRoom(roomCount, itemToAdd, 4, 0, 50);

    // Creature
    strcpy(creatureToAdd, "Basilisk");
    addCreatureToRoom(roomCount, creatureToAdd, 150, 32);

    roomCount++;

    //========> PATH 12 (C)
    // Items
    strcpy(itemToAdd, "Excalibur");
    addItemToRoom(roomCount, itemToAdd, 1, 47, 10);

    // Creature
    strcpy(creatureToAdd, "TraitorSoldier");
    addCreatureToRoom(roomCount, creatureToAdd, 45, 22);

    roomCount++;

    //========> PATH 13 (D)
    roomCount++;

    //========> PATH 14 (FINISH)
    // Creature
    strcpy(creatureToAdd, "NightFury");
    addCreatureToRoom(roomCount, creatureToAdd, 210, 27);

    roomCount++;
}

void saveGame(const char *filename)
{
    char wFileName[MAX_DESCRIPTION] = "";
    strcat(wFileName, "saveFiles/");
    strcat(wFileName, filename);

    FILE *file = fopen(wFileName, "w");
    if (!file)
    {
        perror(">>>ERROR WHILE SAVING...");
        return;
    }

    //========> SAVE PLAYER ATTRIBUTES
    fprintf(file, "PLAYER\n");
    // Health, power, currentRoom, inventory
    fprintf(file, "%d %d %d %d\n", player.health, player.attackPower, player.defensePower, player.currentRoom);
    fprintf(file, "%d\n", player.inventoryCount);
    for (int i = 0; i < INVENTORY_LIMIT; i++)
    {
        if (player.inventory[i] == NULL)
        {
            fprintf(file, "%s %d %d %d %d\n",
                    "EmptySlot", 0, 0, 0, 0);
        }
        else
        {
            fprintf(file, "%s %d %d %d %d\n",
                    player.inventory[i]->description,
                    player.inventory[i]->itemType,
                    player.inventory[i]->attackPower,
                    player.inventory[i]->defensePower,
                    player.inventory[i]->equipped);
        }
    }

    //========> SAVE ROOM ATTRIBUTES
    fprintf(file, "ROOMS\n");
    for (int i = 0; i < MAX_ROOMS; i++)
    {
        // Save itemCount of the room
        fprintf(file, "%d\n", rooms[i].itemCount);

        // Save the items
        for (int j = 0; j < MAX_ITEMS_IN_ROOM; j++)
        {
            if (rooms[i].items[j] == NULL)
                continue;

            fprintf(file, "%s %d %d %d %d\n",
                    rooms[i].items[j]->description,
                    rooms[i].items[j]->itemType,
                    rooms[i].items[j]->attackPower,
                    rooms[i].items[j]->defensePower,
                    rooms[i].items[j]->equipped);
        }

        // Save the creature if exists
        if (rooms[i].creature)
            fprintf(file, "%s %d %d\n", rooms[i].creature->name, rooms[i].creature->health, rooms[i].creature->strength);
        else
            fprintf(file, "NULL\n");
    }

    fclose(file);

    printf(">>>SAVED AS '%s'\n", filename);
}

/*
    This method initializes the game with load values.
    It is called when the game is being load from a load
    file.

    Player and rooms are initialized here with proper values.

    RETURNS FALSE if the file is not found to use in login screen
*/
bool loadGame(const char *filename)
{
    char rFileName[MAX_DESCRIPTION] = "";
    strcat(rFileName, "saveFiles/");
    strcat(rFileName, filename);

    FILE *file = fopen(rFileName, "r");
    if (!file)
    {
        printf(">>>NO SAVE FOUND AS %s\n", filename);
        return false;
    }

    char buffer[MAX_DESCRIPTION];

    //========> LOAD PLAYER ATTRIBUTES
    fscanf(file, "%s", buffer);
    if (strcmp(buffer, "PLAYER") == 0)
    {
        // Health, power, currentRoom, inventory
        fscanf(file, "%d %d %d %d", &player.health, &player.attackPower, &player.defensePower, &player.currentRoom);
        fscanf(file, "%d", &player.inventoryCount);
        for (int i = 0; i < INVENTORY_LIMIT; i++)
        {
            Item *item = malloc(sizeof(Item));
            fscanf(file, "%s %d %d %d %d",
                   item->description,
                   &item->itemType,
                   &item->attackPower,
                   &item->defensePower,
                   &item->equipped);
            player.inventory[i] = item;

            if (item->equipped == 1)
            {
                if (item->itemType == 1)
                    player.attackItem = item;
                else if (item->itemType == 2)
                    player.armor = item;
                else if (item->itemType == 3)
                    player.shield = item;
            }
        }
    }

    //========> LOAD ROOM ATTRIBUTES
    fscanf(file, "%s", buffer);
    if (strcmp(buffer, "ROOMS") == 0)
    {
        for (int i = 0; i < MAX_ROOMS; i++)
        {
            // Load itemCount
            fscanf(file, "%d", &rooms[i].itemCount);

            // Load the items
            for (int j = 0; j < rooms[i].itemCount; j++)
            {
                Item *item = malloc(sizeof(Item));
                fscanf(file, "%s %d %d %d %d",
                       item->description,
                       &item->itemType,
                       &item->attackPower,
                       &item->defensePower,
                       &item->equipped);
                rooms[i].items[j] = item;
            }

            // Load creature if exists
            char creatureName[MAX_DESCRIPTION];
            fscanf(file, "%s", creatureName);
            if (strcmp(creatureName, "NULL") != 0)
            {
                Creature *creature = malloc(sizeof(Creature));
                strcpy(creature->name, creatureName);
                fscanf(file, "%d %d", &creature->health, &creature->strength);
                rooms[i].creature = creature;
            }
        }
    }

    fclose(file);

    printf(">>>SAVE '%s' IS LOADED.\n", filename);
    printf("\n");

    return true;
}

void listSavedGames()
{
    int saveCount = 0;

    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    const char *path = "saveFiles\\*";

    // First file
    hFind = FindFirstFile(path, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf(">>NO SAVE FILES\n");
        return;
    }

    printf("Save History: \n");

    do
    {
        if (findFileData.cFileName[0] != '.')
        {
            saveCount++;
            printf("%d- %s\n", saveCount, findFileData.cFileName);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void exitGame()
{
    printf("You're leaving the forest... Farewell!\n");
    exit(0);
}

// Parse the input into an int value
int parseDirection(const char *direction)
{
    if (strcmp(direction, "up") == 0)
        return 0;
    if (strcmp(direction, "right") == 0)
        return 1;
    if (strcmp(direction, "down") == 0)
        return 2;
    if (strcmp(direction, "left") == 0)
        return 3;
    return -1;
}

void clearScreen()
{
    system("cls");
}

void help()
{
    printf("Login Screen Commands:\n");
    printf("1- start: Start the game\n");
    printf("2- load: Load a game\n");
    printf("3- list: List saved files\n");
    printf("4- help: See game commands\n");
    printf("5- exit: Exit the game\n");
    printf("\n");

    printf("In-Game Commands:\n");
    printf("1- move 'direction': moves to direction\n");
    printf("2- look: See what there are in current room\n");
    printf("3- inventory: See inventory\n");
    printf("4- equip 'item': Equip the item \n");
    printf("5- me: Display player attributes\n");
    printf("6- pickup 'item': Pick up the item\n");
    printf("7- attack: Attack to the creature if exists\n");
    printf("8- attack kill: Attack to the creature until it(or you) is dead\n");
    printf("9- map: Look to the map. (You must find the Map item first)\n");
    printf("10- save: Save the game\n");
    printf("11- load 'game': Load a saved game\n");
    printf("12- list: List saved files\n");
    printf("13- help: See game commands\n");
    printf("14- exit: Exit the game\n");
}