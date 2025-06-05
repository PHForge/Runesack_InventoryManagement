/*
 * Runesack Inventory Management - A text-based RPG inventory system
 * Copyright (c) 2025 PHForge
 *
 * Manage an RPG inventory with adventures, shop interactions, and item management.
 *
 * Licensed under the MIT License.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h> // For setlocale
#ifdef _WIN32
#include <windows.h> // For SetConsoleOutputCP
#endif

#include "utils.h"
#include "inventory.h"
#include "item.h"
#include "shop.h"
#include "adventure.h"

int main() {
    // Configure console locale and encoding
    setlocale(LC_ALL, "C.UTF-8"); // Use system regional settings
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8); // Configure the console for UTF-8
        SetConsoleCP(CP_UTF8);      // Configure input for UTF-8
    #endif

    // Seed the random number generator
    // This is important for generating random numbers in adventures and item selection
    srand(time(NULL));
    // Initialize game settings and load items and inventory
    GameSettings settings = {GAME_LANG_ENGLISH, 50.0f};
    // Load game settings from a file or use default values
    ItemDatabase* db = load_items("items.txt", settings.language);
    if (!db) {
        printf("Failed to load items database.\n");
        return 1;
    }
    // Initialize inventory with the maximum weight from settings
    Inventory* inv = create_inventory(settings.max_weight);
    if (!inv) {
        free_item_database(db);
        printf("Error: Failed to initialize inventory.\n");
        return 1;
    }
    // Load inventory from a file or initialize with default values
    load_inventory(inv, "inventory.txt", db, settings.language);
    display_banner();

    int choice;
    do {
        // Display the main menu and the amount of the user wallet
        printf("\n%s         %s: %d PHGold\n\n", get_message(MSG_MENU_TITLE, settings.language), get_message(MSG_WALLET, settings.language), inv->phgold);
        printf("1. %s\n2. %s\n3. %s\n4. %s\n5. %s\n6. %s\n\n",
               get_message(MSG_ADVENTURE, settings.language),
               get_message(MSG_SHOP, settings.language),
               get_message(MSG_BROWSE, settings.language),
               get_message(MSG_SETTINGS, settings.language),
               get_message(MSG_CREDITS, settings.language),
               get_message(MSG_QUIT, settings.language));
        printf("%s: ", get_message(MSG_YOUR_CHOICE, settings.language));
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("%s\n", get_message(MSG_INVALID_CHOICE, settings.language));
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
                // Go on an adventure
                go_on_adventure(inv, db, settings.language);
                break;
            case 2:
                // Visit the shop
                display_shop(inv, db, settings.language);
                break;
            case 3:
                // Browse the inventory
                display_inventory(inv, settings.language);
                break;
            case 4:
                // Configure settings
                configure_settings(&settings, inv, db);
                break;
            case 5:
                // Display credits
                display_credits(settings.language);
                getchar(); 
                break;
            case 6:
                // Quit the game and save the inventory
                save_inventory(inv, "inventory.txt");
                printf("%s\n", get_message(MSG_QUIT, settings.language));
                break;
            default:
                printf("%s\n", get_message(MSG_INVALID_CHOICE, settings.language));
        }
    } while (choice != 6);
    
    free_inventory(inv); // Free the inventory resources
    free_item_database(db); // Free the item database resources
    return 0;
}