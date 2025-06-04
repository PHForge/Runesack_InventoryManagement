#include <stdio.h>
#include <stdlib.h>
#include "shop.h"

// Sélectionne 3 items aléatoires depuis la base de données
void select_random_items(ItemDatabase* db, Item** selected_items, int num_items) {
    if (!db || db->count == 0 || num_items > db->count) return;

    // Créer un tableau d'indices pour éviter les doublons
    int* indices = malloc(db->count * sizeof(int));
    if (!indices) return;
    for (int i = 0; i < db->count; i++) {
        indices[i] = i;
    }

    // Mélanger les indices (algorithme de Fisher-Yates)
    for (int i = db->count - 1; i > 0 && i >= db->count - num_items; i--) {
        int j = get_random_int(0, i);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Sélectionner les items correspondants aux indices
    for (int i = 0; i < num_items; i++) {
        selected_items[i] = db->items[indices[db->count - 1 - i]];
    }

    free(indices);
}

// Affiche la boutique et gère les achats
void display_shop(Inventory* inv, ItemDatabase* db, int language) {
    if (!inv || !db || db->count == 0) {
        printf("%s\n", get_message(MSG_INVENTORY_EMPTY, language));
        return;
    }

    printf("\n=== %s ===\n", get_message(MSG_SHOP, language));
    printf("%s: %d PHGold\n\n", get_message(MSG_WALLET, language), inv->phgold);

    // Sélectionner 3 items aléatoires
    Item* shop_items[3] = {NULL, NULL, NULL};
    int num_items = db->count < 3 ? db->count : 3;
    select_random_items(db, shop_items, num_items);

    // Afficher les items disponibles
    for (int i = 0; i < num_items; i++) {
        printf("\n%d. %s (%d PHGold)\n", i + 1,
               language == GAME_LANG_ENGLISH ? shop_items[i]->name_en : shop_items[i]->name_fr,
               shop_items[i]->value);
        print_item(shop_items[i], language);
    }

    // Ajouter une option pour quitter
    printf("\n%d. %s\n", num_items + 1, get_message(MSG_BACK, language));
    printf("\n%s: ", get_message(MSG_YOUR_CHOICE, language));

    int choice;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > num_items + 1) {
        clear_input_buffer();
        printf("%s\n", get_message(MSG_INVALID_CHOICE, language));
        return;
    }
    clear_input_buffer();

    if (choice == num_items + 1) {
        printf("%s\n", get_message(MSG_BACK, language));
        return;
    }

    // Traiter l'achat
    Item* selected_item = shop_items[choice - 1];
    if (inv->phgold >= selected_item->value) {
        // Créer une copie de l'item pour l'ajouter à l'inventaire
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

        // Ajouter l'item à l'inventaire
        add_item(inv, new_item, language);
        if (inv->total_weight + new_item->weight <= inv->max_weight) {
            // Déduire le coût si l'item a été ajouté avec succès
            inv->phgold -= selected_item->value;
            printf("\n/!\\ %s: %s /!\\\n",
                   get_message(MSG_ITEM_CREATED, language),
                   language == GAME_LANG_ENGLISH ? new_item->name_en : new_item->name_fr);
        }
    } else {
        printf("%s\n", get_message(MSG_NOT_ENOUGH_GOLD, language));
    }
}