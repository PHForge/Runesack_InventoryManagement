#include <stdio.h>
#include <stdlib.h>
#include "shop.h"

// Select 3 random items from the database
void select_random_items(ItemDatabase* db, Item** selected_items, int num_items) {
    if (!db || db->count == 0 || num_items > db->count) return; // Ensure the database is valid and has enough items

    // Create an index table to avoid duplicates
    int* indices = malloc(db->count * sizeof(int));
    if (!indices) return; 
    for (int i = 0; i < db->count; i++) { // Initialize indices with item positions
        indices[i] = i; 
    } 

    // Shuffling the indices (Fisher-Yates algorithm)
    // This algorithm ensures that we randomly select items without duplicates 
    for (int i = db->count - 1; i > 0 && i >= db->count - num_items; i--) {
        int j = get_random_int(0, i);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Select the last num_items indices as the selected items
    // This ensures that we get a random selection of items
    for (int i = 0; i < num_items; i++) {
        selected_items[i] = db->items[indices[db->count - 1 - i]];
    }

    free(indices);
}

// Manages the purchase of items
void buy_items(Inventory* inv, ItemDatabase* db, int language) {
    if (!inv || !db || db->count == 0) { // Check if the inventory or database is valid
        printf("%s\n", get_message(MSG_INVENTORY_EMPTY, language));
        return;
    }

    printf("\n=== %s ===\n\n", get_message(MSG_SHOP, language));
    printf("%s: %d PHGold\n\n", get_message(MSG_WALLET, language), inv->phgold);

   
    Item* shop_items[3] = {NULL, NULL, NULL}; // Array to hold the selected items for the shop
    int num_items = db->count < 3 ? db->count : 3; // Number of items to display (up to 3)
    select_random_items(db, shop_items, num_items); // Select random items from the database

    // Show items available for purchase
    for (int i = 0; i < num_items; i++) {
        printf("\n%d. %s (%d PHGold)\n", i + 1, 
               language == GAME_LANG_ENGLISH ? shop_items[i]->name_en : shop_items[i]->name_fr,
               shop_items[i]->value);
        print_item(shop_items[i], language);
    }

    // Add an option to go back
    printf("\n%d. %s\n", num_items + 1, get_message(MSG_BACK, language));
    printf("\n%s: ", get_message(MSG_YOUR_CHOICE, language));

    // Get user input for item selection
    int choice;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > num_items + 1) {
        clear_input_buffer();
        printf("%s\n", get_message(MSG_INVALID_CHOICE, language));
        return;
    }
    clear_input_buffer();

    // Check if the user wants to go back
    // If the choice is greater than the number of items, it means the user wants to go back
    if (choice == num_items + 1) {
        printf("%s\n", get_message(MSG_BACK, language));
        return;
    }

    // Check if the user has enough PHGold to buy the selected item
    Item* selected_item = shop_items[choice - 1];
    if (inv->phgold >= selected_item->value) {
        // Create a copy of the item to add it to inventory
        Item* new_item = create_item(
            selected_item->name_en, selected_item->name_fr,
            selected_item->properties.type, selected_item->properties.rarity,
            selected_item->properties.state, selected_item->description_en,
            selected_item->description_fr, selected_item->weight,
            selected_item->value, selected_item->passive_effect_en,
            selected_item->passive_effect_fr, &selected_item->specific);

        if (!new_item) {
            printf("%s\n", get_message(MSG_FAILED_TO_CREATE_ITEM, language));
            return;
        }

        // Add the item to the inventory
        add_item(inv, new_item, language);
        if (inv->total_weight + new_item->weight <= inv->max_weight) {
            // If the item was successfully added, deduct its value from PHGold
            inv->phgold -= selected_item->value;
            printf("\n/!\\ %s: %s /!\\\n",
                   get_message(MSG_ITEM_CREATED, language),
                   language == GAME_LANG_ENGLISH ? new_item->name_en : new_item->name_fr);
        }
    } else {
        printf("%s\n", get_message(MSG_NOT_ENOUGH_GOLD, language));
    }
}

// Displays the shop menu and allows the player to buy or sell items
void display_shop(Inventory* inv, ItemDatabase* db, int language) {
    int keep_running = 1; // Flag to control the loop for the shop menu
    const int menu_options[] = {MSG_SHOP, MSG_SELL_ITEMS, MSG_BACK};
    const int num_options = 3;

    
    while (keep_running) {
        printf("\n=== %s ===\n", get_message(MSG_SHOP, language));
        printf("%s: %d PHGold\n\n", get_message(MSG_WALLET, language), inv->phgold);

        // Display the menu options
        for (int i = 0; i < num_options; i++) {
            printf("%d. %s\n", i + 1, get_message(menu_options[i], language));
        }
        printf("\n%s: ", get_message(MSG_YOUR_CHOICE, language));

        // Get user input for menu selection
        int choice;
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > num_options) {
            clear_input_buffer();
            printf("%s\n", get_message(MSG_INVALID_CHOICE, language));
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: // Buy items
                buy_items(inv, db, language);
                break;
            case 2: // Sell items
                sell_items(inv, language);
                break;
            case 3: // Go back to the main menu
                printf("%s\n", get_message(MSG_BACK, language));
                keep_running = 0;
                break;
        }
    }
}

// Manages the sale of items from the inventory
void sell_items(Inventory* inv, int language) {
    if (!inv || !inv->head) { // Check if the inventory is valid and not empty
        printf("\n/!\\ %s /!\\\n", get_message(MSG_INVENTORY_EMPTY, language));
        return;
    }

    printf("\n=== %s ===\n\n", get_message(MSG_SELL_ITEMS, language));
    printf("%s: %d PHGold\n\n", get_message(MSG_WALLET, language), inv->phgold);

    
    InventoryNode* current = inv->head; // Start from the head of the linked list
    int index = 1; 
    // Display items with their index and value
    while (current) { 
        printf("%d. %s (%d PHGold)\n", index,
               language == GAME_LANG_ENGLISH ? current->item->name_en : current->item->name_fr,
               current->item->value);
        current = current->next;
        index++;
    }

    // Add an option to go back
    printf("\n%d. %s\n", index, get_message(MSG_BACK, language));
    printf("\n%s: ", get_message(MSG_YOUR_CHOICE, language));

    // Get user input for item selection
    int choice;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > index) {
        clear_input_buffer();
        printf("%s\n", get_message(MSG_INVALID_CHOICE, language));
        return;
    }
    clear_input_buffer();

    // Check if the user wants to go back
    // If the choice is equal to the index, it means the user wants to go back
    if (choice == index) {
        printf("%s\n", get_message(MSG_BACK, language));
        return;
    }

    // Find the item to sell based on the user's choice
    current = inv->head;
    InventoryNode* prev = NULL;
    int current_index = 1;
    // Traverse the linked list to find the item at the specified index
    while (current && current_index < choice) {
        prev = current;
        current = current->next;
        current_index++;
    }

    // If the item was found, proceed with the sale
    if (current) {
        // Add the item's value to PHGold and reduce the total weight
        inv->phgold += current->item->value;
        inv->total_weight -= current->item->weight;

        // Remove the item from the inventory
        if (prev) {
            prev->next = current->next;
        } else {
            inv->head = current->next;
        }

        printf("\n/!\\ %s: %s (%d PHGold) /!\\\n",
                get_message(MSG_ITEM_SOLD, language),
                language == GAME_LANG_ENGLISH ? current->item->name_en : current->item->name_fr,
                current->item->value);

        // Free the item and the node
        free_item(current->item);
        free(current);
    }
}

