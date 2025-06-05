#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "adventure.h"

// Structure pour stocker les scénarios d'aventure
typedef struct {
    const char* description_en;
    const char* description_fr;
} AdventureScenario;

// Liste des 15 scénarios d'aventure
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

// Nombre total de scénarios
#define NUM_SCENARIOS 15

// Sélectionne un item aléatoire depuis la base de données
static Item* select_random_item(ItemDatabase* db) {
    if (!db || db->count == 0) return NULL;
    int index = get_random_int(0, db->count - 1);
    return db->items[index];
}

// Gère l'aventure
void go_on_adventure(Inventory* inv, ItemDatabase* db, int language) {
    if (!inv || !db) {
        printf("%s\n", get_message(MSG_INVENTORY_EMPTY, language));
        return;
    }

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Choisir un scénario aléatoire
    int scenario_index = get_random_int(0, NUM_SCENARIOS - 1);
    const AdventureScenario* scenario = &scenarios[scenario_index];

    // Afficher le scénario
    printf("\n=== %s ===\n\n", get_message(MSG_ADVENTURE, language));
    printf("%s\n", language == GAME_LANG_ENGLISH ? scenario->description_en : scenario->description_fr);

    // Afficher le message de succès
    printf("\n/!\\ %s /!\\\n", get_message(MSG_ADVENTURE_SUCCESS, language));

    // Déterminer la récompense (PHGold, item, ou les deux)
    int reward_type = get_random_int(1, 3); // 1: PHGold, 2: Item, 3: Les deux
    int gold_reward = 0;
    Item* reward_item = NULL;

    if (reward_type == 1 || reward_type == 3) {
        // Récompense en PHGold (entre 10 et 100)
        gold_reward = get_random_int(250, 1000);
        inv->phgold += gold_reward;
        printf("%s: %d PHGold\n", get_message(MSG_REWARD_GOLD, language), gold_reward);
    }

    if (reward_type == 2 || reward_type == 3) {
        // Récompense avec un item
        Item* selected_item = select_random_item(db);
        if (selected_item) {
            // Créer une copie de l'item
            reward_item = create_item(
                selected_item->name_en, selected_item->name_fr,
                selected_item->properties.type, selected_item->properties.rarity,
                selected_item->properties.state, selected_item->description_en,
                selected_item->description_fr, selected_item->weight,
                selected_item->value, selected_item->passive_effect_en,
                selected_item->passive_effect_fr, &selected_item->specific
            );

            if (reward_item) {
                // Vérifier le poids de l'inventaire
                if (inv->total_weight + reward_item->weight <= inv->max_weight) {
                    add_item(inv, reward_item, language);
                    printf("%s: %s\n", get_message(MSG_REWARD_ITEM, language),
                           language == GAME_LANG_ENGLISH ? reward_item->name_en : reward_item->name_fr);
                } else {
                    printf("%s: %s\n", get_message(MSG_ITEM_ABANDONED, language),
                           language == GAME_LANG_ENGLISH ? reward_item->name_en : reward_item->name_fr);
                    free_item(reward_item); // Libérer l'item non ajouté
                }
            } else {
                printf("%s\n", get_message(MSG_FAILED_TO_CREATE_ITEM, language));
            }
        }
    }

    printf("\n%s\n", get_message(MSG_BACK, language));
}