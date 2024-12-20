#include "../headerFiles/Game.h"
#include "../headerFiles/Room.h"
#include "../headerFiles/Item.h"
#include "../headerFiles/Creature.h"
#include "../headerFiles/Player.h"

int main()
{
    char command[256];
    initGame();

    printf("||||||||||||||||||||||===================LONELY FOREST===================||||||||||||||||||||||\n");

    // Login Screen
    while (true)
    {
        printf("\n> START OR LOAD GAME('help' to see game commands): ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;
        if (loginScreen(command))
            break;
    }

    // In-game
    while (true)
    {
        printf("\n> Command: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character
        handleCommand(command);
    }
    return 0;
}