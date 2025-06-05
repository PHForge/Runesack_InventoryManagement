#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "adventure.h"

// Structure for storing adventure scenarios
typedef struct {
    const char* description_en;
    const char* description_fr;
} AdventureScenario;

// List of 15 adventure scenarios
static const AdventureScenario scenarios[] = {
    {"You venture into a dark, deep forest.", "Vous vous aventurez dans une forêt sombre et profonde."},
    {"You explore a legendary labyrinth.", "Vous explorez un labyrinthe légendaire."},
    {"You dig in a mysterious mine.", "Vous creusez dans une mine mystérieuse."},
    {"You face an army of dangerous monsters.", "Vous affrontez une armée de monstres dangereux."},
    {"You solve the riddle of a curious character.", "Vous résolvez l'énigme d'un personnage curieux."},
    {"You climb an impossible mountain.", "Vous gravissez une montagne impossible."},
    {"You play a game with a werewolf.", "Vous jouez à un jeu avec un loup-garou."},
    {"You search for treasure in a haunted castle.", "Vous cherchez un trésor dans un château hanté."},
    {"You navigate a treacherous swamp.", "Vous naviguez dans un marais périlleux."},
    {"You investigate an ancient ruin.", "Vous explorez une ruine ancienne."},
    {"You sail across a stormy sea.", "Vous naviguez sur une mer tumultueuse."},
    {"You infiltrate a bandit hideout.", "Vous vous infiltrez dans un repaire de bandits."},
    {"You chase a mythical creature in the desert.", "Vous poursuivez une créature mythique dans le désert."},
    {"You uncover secrets in a forgotten temple.", "Vous découvrez des secrets dans un temple oublié."},
    {"You survive a night in a cursed village.", "Vous survivez une nuit dans un village maudit."}
};

// Total number of scenarios
#define NUM_SCENARIOS 15

// Selects a random item from the database
static Item* select_random_item(ItemDatabase* db) {
    if (!db || db->count == 0) return NULL;
    int index = get_random_int(0, db->count - 1);
    return db->items[index];
}

// Manage the adventure
void go_on_adventure(Inventory* inv, ItemDatabase* db, int language) {
    if (!inv || !db) {
        printf("%s\n", get_message(MSG_INVENTORY_EMPTY, language));
        return;
    }

    // Initialize the random number generator
    srand(time(NULL));
    // Select a random adventure scenario
    int scenario_index = get_random_int(0, NUM_SCENARIOS - 1);
    // Ensure the scenario index is within bounds
    const AdventureScenario* scenario = &scenarios[scenario_index];

    // Show scenario
    printf("\n=== %s ===\n\n", get_message(MSG_ADVENTURE, language));
    printf("%s\n", language == GAME_LANG_ENGLISH ? scenario->description_en : scenario->description_fr);

    // Show success message
    printf("\n/!\\ %s /!\\\n", get_message(MSG_ADVENTURE_SUCCESS, language));

    // Determine the reward (PHGold, item, or both)
    int reward_type = get_random_int(1, 3); // 1: PHGold, 2: Item, 3: Both
    int gold_reward = 0;
    Item* reward_item = NULL;

    if (reward_type == 1 || reward_type == 3) {
        // PHGold reward (between 250 and 1000)
        gold_reward = get_random_int(250, 1000);
        inv->phgold += gold_reward;
        printf("%s: %d PHGold\n", get_message(MSG_REWARD_GOLD, language), gold_reward);
    }

    if (reward_type == 2 || reward_type == 3) {
        // Item reward
        Item* selected_item = select_random_item(db);
        if (selected_item) {
            // Create the item with the selected properties
            reward_item = create_item(
                selected_item->name_en, selected_item->name_fr,
                selected_item->properties.type, selected_item->properties.rarity,
                selected_item->properties.state, selected_item->description_en,
                selected_item->description_fr, selected_item->weight,
                selected_item->value, selected_item->passive_effect_en,
                selected_item->passive_effect_fr, &selected_item->specific
            );

            if (reward_item) {
                // Check if the item can be added to the inventory
                if (inv->total_weight + reward_item->weight <= inv->max_weight) {
                    add_item(inv, reward_item, language);
                    printf("%s: %s\n", get_message(MSG_REWARD_ITEM, language),
                           language == GAME_LANG_ENGLISH ? reward_item->name_en : reward_item->name_fr);
                } else {
                    printf("%s: %s\n", get_message(MSG_ITEM_ABANDONED, language),
                           language == GAME_LANG_ENGLISH ? reward_item->name_en : reward_item->name_fr);
                    free_item(reward_item); // Free the item if it cannot be added
                }
            } else {
                printf("%s\n", get_message(MSG_FAILED_TO_CREATE_ITEM, language));
            }
        }
    }

    printf("\n%s\n", get_message(MSG_BACK, language));
}