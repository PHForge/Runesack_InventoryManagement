/*
 * Runesack Inventory Management - A text-based RPG inventory system
 * Copyright (c) 2025 PHForge
 *
 * Manage an RPG inventory with adventures, shop interactions, and item sorting.
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

int main() {
    // Configure console locale and encoding
    setlocale(LC_ALL, "C.UTF-8"); // Use system regional settings
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8); // Configure the console for UTF-8
        SetConsoleCP(CP_UTF8);      // Configure input for UTF-8
    #endif

    srand(time(NULL));
    GameSettings settings = {GAME_LANG_ENGLISH, 50.0f};
    Inventory* inv = create_inventory(settings.max_weight); // Créer l'inventaire
    if (!inv) {
        printf("\nError: Failed to initialize inventory.\n");
        return 1;
    }
    display_banner();

    Item* current_item = NULL; // Variable to store the created object

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
                printf("\nLOL, adventure not implemented yet!\n");
                break;
            case 2:
                printf("\nLOL, shop not implemented yet!\n");
                break;
            case 3:
                display_inventory(inv, settings.language);
                break;
            case 4:
                configure_settings(&settings, inv);
                break;
            case 5:
                display_credits(settings.language);
                getchar();
                break;
            case 6:
                printf("%s\n", get_message(MSG_QUIT, settings.language));
                break;
            default:
                printf("%s\n", get_message(MSG_INVALID_CHOICE, settings.language));
        }
    } while (choice != 6);

    free_inventory(inv);
    return 0;
}