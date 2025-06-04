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

int main() {
    // Configure console locale and encoding
    setlocale(LC_ALL, "C.UTF-8"); // Use system regional settings
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8); // Configure the console for UTF-8
        SetConsoleCP(CP_UTF8);      // Configure input for UTF-8
    #endif

    srand(time(NULL));
    GameSettings settings = {GAME_LANG_ENGLISH, 50.0f};
    ItemDatabase* db = load_items("items.txt", settings.language);
    if (!db) {
        printf("Failed to load items database.\n");
        return 1;
    }
    Inventory* inv = create_inventory(settings.max_weight);
    if (!inv) {
        free_item_database(db);
        printf("Error: Failed to initialize inventory.\n");
        return 1;
    }
    load_inventory(inv, "inventory.txt", db, settings.language);
    display_banner();

    int choice;
    do {
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
                printf("LOL, adventure not implemented yet!\n");
                break;
            case 2:
                display_shop(inv, db, settings.language);
                break;
            case 3:
                display_inventory(inv, settings.language);
                break;
            case 4:
                configure_settings(&settings, inv, db);
                break;
            case 5:
                display_credits(settings.language);
                getchar();
                break;
            case 6:
                save_inventory(inv, "inventory.txt");
                printf("%s\n", get_message(MSG_QUIT, settings.language));
                break;
            default:
                printf("%s\n", get_message(MSG_INVALID_CHOICE, settings.language));
        }
    } while (choice != 6);
    
    free_inventory(inv);
    free_item_database(db);
    return 0;
}