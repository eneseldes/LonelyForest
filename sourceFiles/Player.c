#include "../headerFiles/Player.h"

#define INVENTORY_LIMIT 7
#define MAX_ITEMS_IN_ROOM 5

void showMap()
{
    for (int i = 0; i < INVENTORY_LIMIT; i++)
    {
        if (player.inventory[i] == NULL)
            continue;

        if (strcmp(player.inventory[i]->description, "Map") == 0)
        {
            printf("        +---+\n");
            printf("        |\n");
            printf("        +           +---N\n");
            printf("        |           |\n");
            printf("+---+---+---+---+---+\n");
            printf("            |       |\n");
            printf("            +       +\n");
            printf("            |\n");
            printf("            +---+\n");
            return;
        }
    }

    printf("You don't have a map.\n");
}

void move(const char *direction)
{
    int dir = parseDirection(direction);

    if (dir == -1)
    {
        printf("Invalid direction. Use up, down, left, or right.\n");
        return;
    }

    int nextRoom = rooms[player.currentRoom].connections[dir];

    // Block changing room if there is a monster or no connection
    if (rooms[player.currentRoom].creature)
    {
        printf("A monster is staring at you. You cannot change path.\n");
    }
    else if (nextRoom == -1)
    {
        if (player.health > 3)
            player.health -= 2;

        printf("Watch out, thorny bushes have blocked this way! (Remaining Health: %d)\n", player.health);
    }
    else
    {
        player.currentRoom = nextRoom;
        printf("You walk silently...\n");
        printf("%s", rooms[player.currentRoom].description);
    }

    // Inform user about monster
    if (rooms[player.currentRoom].creature)
    {
        printf("Thread!\n");
    }
}

void look()
{
    bool hasConnection = false;

    Room *currentRoom = &rooms[player.currentRoom];

    printf("%s\n", currentRoom->description);

    // Print creature
    if (currentRoom->creature)
    {
        printf("You see a %s here.\n", currentRoom->creature->name);
        printf("\n");
    }

    // List the items in the room
    if (currentRoom->itemCount > 0)
    {
        printf("Items in the room:\n");
        for (int i = 0; i < MAX_ITEMS_IN_ROOM; i++)
        {
            if (currentRoom->items[i] == NULL)
                continue;
            else
                printf("- %s\n", currentRoom->items[i]->description);
        }

        printf("\n");
    }

    // Print the walkable paths
    printf("Open paths: ");
    for (int i = 0; i < 4; i++)
    {
        if (currentRoom->connections[i] != -1)
        {
            hasConnection = true;

            switch (i)
            {
            case 0:
                printf("up ");
                break;
            case 1:
                printf("right ");
                break;
            case 2:
                printf("down ");
                break;
            case 3:
                printf("left");
                break;
            }
        }
    }

    // At the end of the game
    if (!hasConnection)
    {
        printf("Death");
    }

    printf("\n");
}

void inventory()
{
    if (player.inventoryCount == 0)
    {
        printf("Your inventory is empty.\n");
        return;
    }

    printf("You have the following items:\n");
    for (int i = 0; i < INVENTORY_LIMIT; i++)
    {
        int equipped = 0;

        // Cath NULL
        if (player.inventory[i] == NULL)
        {
            printf("%d- Empty Slot\n", i + 1);
            continue;
        }

        // If the iterated item and current equipped item is equal, print it as Equipped
        if (strcmp(player.inventory[i]->description, player.attackItem->description) == 0 ||
            strcmp(player.inventory[i]->description, player.armor->description) == 0 ||
            strcmp(player.inventory[i]->description, player.shield->description) == 0)
            equipped = 1;

        printf("%d- %s%s\n   ->Attack Rate: %d\n   ->DefenseRate: %d\n",
               i + 1, player.inventory[i]->description, equipped == 1 ? " (Equipped)" : "",
               player.inventory[i]->attackPower, player.inventory[i]->defensePower);
    }
}

/*
    Inventory management is a bit tricky.

    Since there is no array lists on C, items are stored
    in an array. And if an item is dropped or picked up,
    it creates a NULL value in the middle of the array
    sometimes.

    To control it:
    -When an item is picked up, it is being initialized into
    the nearest NULL value in the inventory starting from 0.
    itemCount is still being incremented to control if the
    inventory exceeds the limit.
    -With the same way, when an item is dropped, it is being
    initialized into the nearest NULL value on 'items' array
    in a room.

    To avoid these NULL values, catch and overcome them with
    'continue' in the loop.
*/
void pickup(const char *item)
{
    Room *currentRoom = &rooms[player.currentRoom];

    // Block pickup when there is a creature in the room
    if (currentRoom->creature)
    {
        printf("A monster is staring at you. You cannot pick up an item.\n");
        return;
    }

    // Block pickup when inventory is full
    if (player.inventoryCount >= INVENTORY_LIMIT)
    {
        printf("Your inventory is full!\n");
        return;
    }

    // Search the room for item to pick up
    for (int i = 0; i < MAX_ITEMS_IN_ROOM; i++)
    {
        // Skip the empty slot
        if (currentRoom->items[i] == NULL)
            continue;

        // Found item to pick up
        if (strcmp(currentRoom->items[i]->description, item) == 0)
        {
            if (currentRoom->items[i]->itemType == 5)
                printf("You cannot equip Map.\n");
            

            // Special pick up for elixirs
            if (currentRoom->items[i]->itemType == 4)
            {
                player.health = fmin(150, player.health + currentRoom->items[i]->defensePower);
                printf("You found and drank an elixir of life.\n(Current Health: %d)\n", player.health);

                currentRoom->items[i] = NULL;
                currentRoom->itemCount--;
                return;
            }

            // Search for an empty slot in inventory
            for (int j = 0; j < INVENTORY_LIMIT; j++)
            {
                if (player.inventory[j] == NULL)
                {
                    player.inventory[j] = currentRoom->items[i];
                    player.inventoryCount++;

                    currentRoom->items[i] = NULL;
                    currentRoom->itemCount--;

                    printf("You picked up the %s.\n", item);
                    return;
                }
            }
        }
    }

    printf("Item not found in the room.\n");
}

void equip(const char *item)
{
    for (int i = 0; i < player.inventoryCount; i++)
    {
        if (strcmp(player.inventory[i]->description, item) == 0)
        {
            // Check if it is already equipped
            if (player.inventory[i]->equipped == 1)
            {
                printf("%s is already equipped.\n", item);
                return;
            }

            // Block equip for map and elixirs
            if (player.inventory[i]->itemType == 4 || player.inventory[i]->itemType == 5)
            {
                printf("You cannot equip %s.\n", player.inventory[i]->description);
                return;
            }

            printf("Equipped %s.\n", item);

            // Set new equipnesses
            player.attackItem->equipped = 0;
            player.inventory[i]->equipped = 1;

            // Equip the item here with respect to its type
            switch (player.inventory[i]->itemType)
            {
            case 1:
                player.attackItem = player.inventory[i];
                break;
            case 2:
                player.armor = player.inventory[i];
                break;
            case 3:
                player.shield = player.inventory[i];
                break;
            }

            // Compute new power
            player.attackPower = 5 + player.attackItem->attackPower + player.armor->attackPower + player.shield->attackPower;
            player.defensePower = 0 + player.attackItem->defensePower + player.armor->defensePower + player.shield->defensePower;
            return;
        }
    }

    printf("Item not found in your inventory.\n");
}

void drop(const char *item)
{
    Room *currentRoom = &rooms[player.currentRoom];

    // Inform user of dropping main equipment is not allowed
    if (strcmp(item, "Handfist") == 0 || strcmp(item, "Shirt") == 0 || strcmp(item, "Drape") == 0)
    {
        printf("You cannot drop your main equipment.\n");
        return;
    }

    // Search inventory for the item to drop
    for (int i = 0; i < INVENTORY_LIMIT; i++)
    {
        // Catch NULL
        if (player.inventory[i] == NULL)
            continue;

        if (strcmp(player.inventory[i]->description, item) == 0)
        {
            // Block drop if room slots are full
            if (currentRoom->itemCount == MAX_ITEMS_IN_ROOM)
            {
                printf("You couldn't drop %s. The room is full of items!\n", player.inventory[i]->description);
                return;
            }

            // Block drop on equipped item
            if (player.inventory[i]->equipped == 1)
            {
                printf("You cannot drop an item you equipped.\n");
                return;
            }

            // Search for an empty sloat in the room
            for (int j = 0; j < MAX_ITEMS_IN_ROOM; j++)
            {
                // Reach to the empty slot
                if (currentRoom->items[j] == NULL)
                {
                    // Add dropped item to room
                    currentRoom->items[j] = player.inventory[i];
                    currentRoom->itemCount++;

                    // Remove item from inventory
                    printf("%s dropped.\n", player.inventory[i]->description);
                    player.inventory[i] = NULL;
                    player.inventoryCount--;

                    return;
                }
            }
        }
    }

    printf("Item not found in your inventory.\n");
}

void checkYourself()
{
    // Power and health
    printf("Health: %d\nAttack Power: %d\nDefense Power: %d\n",
           player.health, player.attackPower, player.defensePower);

    printf("\n");

    // Equipped items
    printf("Attack Item: %s\nArmor: %s\nShield: %s\n",
           player.attackItem->description, player.armor->description, player.shield->description);
}

void attack(const char *kill)
{
    Room *currentRoom = &rooms[player.currentRoom];

    // Check for creature
    if (!currentRoom->creature)
    {
        printf("There is nothing to attack here.\n");
        return;
    }

    Creature *creature = currentRoom->creature;
    int heal = creature->strength / 2; // To heal player after battle

    // Combat system: One attack player, one attack creature
    // if user enters 'attack kill', continue fighting until one of them is dead.
    while (creature->health > 0 && player.health > 0)
    {
        // Player attacks
        creature->health -= player.attackPower;
        printf("You hit the %s for %d damage.\n", creature->name, player.attackPower);

        if (creature->health <= 0)
        {
            // End game
            if (strcmp(creature->name, "NightFury") == 0)
            {
                printf("You killed the nightmare of the forest! History will remember you!!!\n");
                printf("||||||||||||||||||||||===================END===================||||||||||||||||||||||\n");
            }

            // Heal player with respect to creature strength and delete creature
            printf("You defeated the %s!\n(Remaining Health: %d(+%d))\n", creature->name, player.health, heal);
            player.health = fmin(150, player.health + heal);

            free(currentRoom->creature);
            currentRoom->creature = NULL;
            return;
        }

        // Creature attacks
        player.health -= fmax(creature->strength - player.defensePower, 0);
        printf("The %s hit you for %d (-%d) damage.\n", 
            creature->name, 
            creature->strength, 
            (int)fmin(creature->strength, player.defensePower));

        if (player.health <= 0)
        {
            printf("You have been defeated! Game over.\n");
            exit(0);
        }

        // If user did not enter attack 'kill', break the loop
        if (strcmp(kill, "kill") != 0)
            return;
    }
}