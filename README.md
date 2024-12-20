# LonelyForest

## Overview

This is a text-based adventure game where players interact with the game world using typed commands. The game offers a variety of functionalities, including starting a new game, loading saved progress, interacting with the environment, and managing inventory.
User wakes up in a quiet forest and tries to escape from there.

## Features

### Login Screen Commands

The following commands are available on the login screen:
- start: Starts a new game.
- load: Loads a previously saved game.
- list: Lists all saved game files.
- help: Displays a list of available game commands.
- exit: Exits the game.

### In-Game Commands

Once in the game, the following commands can be used:

- move 'direction': Moves the player in the specified direction.

- look: Displays the items or entities in the current room.

- inventory: Shows the player's inventory.

- equip 'item': Equips a specified item from the inventory.

- me: Displays the player's attributes (e.g., health, strength).

- pickup 'item': Picks up an item in the current room.

- attack: Attacks a creature in the current room if one exists.

- attack kill: Repeatedly attacks the creature until either it or the player is dead.

- map: Displays the map if the player has acquired the Map item.

- save: Saves the current game state.

- load 'game': Loads a specific saved game.

- list: Lists all saved game files.

- help: Displays a list of available commands.

- exit: Exits the game.

## Error Handling

The game includes robust error-handling mechanisms to enhance the user experience. Common error scenarios and their handling:

### Invalid Commands

If a player enters an unrecognized command, the game will display: "Invalid command. Try again."

### Invalid Parameters

If the parameter is missing or invalid, display an appropriate error message, such as: 

- Invalid direction. Use up, down, left, or right.

### Handling Unique Error Scenarios

In drop and pick up mechanizm, if the room or inventory's capacity is exceeded, the game will:

- Inventory is full.
- Room is full of items.

### File Errors

Handle errors such as missing files or file corruption by displaying messages like:

- Save file not found.


### Gameplay Errors

Prevent actions that are not possible, such as attacking when no creature is present or moving in an invalid direction. Or picking up an item when there is no item in the room. Or moving outside of the map.

- No creature to attack.
- You cannot move in that direction. Thorny bushes!!
- There is no item in this room.
- Item not found in the inventory.
- You cannot drop the item you equipped.
