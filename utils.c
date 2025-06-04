#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"


// Returns a random integer
int get_random_int(int min, int max) {
    return min + (rand() % (max - min + 1));
}

// Clears input buffer
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Displays retro ASCII banner
void display_banner(void) {
    printf("\n");
    printf("   ____ _  _ _  _ ____ ____ ____ ____ _  _ \n");
    printf("   |__/ |  | |\\ | |___ [__  |__| |    |_/  \n");
    printf("   |  \\ |__| | \\| |___ ___] |  | |___ | \\_ \n");
    printf("\n");
    printf("\n        by PHForge\n\n");
}

// Placeholder for translations
const char* get_message(int message_id, int language) {
    static const char* messages[2][110] = {
        // English
        {
            "=== Inventory Management System ===", // MSG_MENU_TITLE - 1
            "Go on an adventure",              // MSG_ADVENTURE
            "Visit shop",                      // MSG_SHOP
            "Browse inventory",                // MSG_BROWSE
            "Settings",                        // MSG_SETTINGS
            "Current settings",                // MSG_ACTUAL_SETTINGS
            "Credits",                         // MSG_CREDITS
            "Quit",                            // MSG_QUIT
            "Invalid choice.",                 // MSG_INVALID_CHOICE
            "Change language",                 // MSG_CHANGE_LANGUAGE - 10
            "Change max weight",               // MSG_CHANGE_MAX_WEIGHT
            "Current max weight",              // MSG_ACTUAL_MAX_WEIGHT
            "Add item to the game",            // MSG_ADD_ITEM
            "Back",                            // MSG_BACK
            "English",                         // MSG_ENGLISH
            "French",                          // MSG_FRENCH
            "Language updated",                // MSG_LANGUAGE_UPDATED
            "Max weight updated to",           // MSG_MAX_WEIGHT_UPDATED
            "Invalid weight.",                 // MSG_INVALID_WEIGHT
            "Item created: ",                  // MSG_ITEM_CREATED - 20
            "Failed to create item.",          // MSG_FAILED_TO_CREATE_ITEM
            "Enter item name",                 // MSG_ENTER_ITEM_NAME
            "Select item type",                // MSG_SELECT_ITEM_TYPE
            "Select item rarity",              // MSG_SELECT_ITEM_RARITY
            "Select item state",               // MSG_SELECT_ITEM_STATE
            "Enter item description",          // MSG_ENTER_ITEM_DESCRIPTION
            "Enter item weight",               // MSG_ENTER_ITEM_WEIGHT
            "Enter item value",                // MSG_ENTER_ITEM_VALUE
            "Enter passive effect",            // MSG_ENTER_PASSIVE_EFFECT
            "Enter min damage",                // MSG_ENTER_MIN_DAMAGE - 30
            "Enter max damage",                // MSG_ENTER_MAX_DAMAGE
            "Enter damage type",               // MSG_ENTER_DAMAGE_TYPE
            "Enter durability",                // MSG_ENTER_DURABILITY
            "Enter range",                     // MSG_ENTER_RANGE
            "Enter attack speed",              // MSG_ENTER_ATTACK_SPEED
            "Enter defense",                   // MSG_ENTER_DEFENSE
            "Enter resistances",               // MSG_ENTER_RESISTANCES
            "Select slot",                     // MSG_SELECT_SLOT
            "Enter movement penalty",          // MSG_ENTER_MOVEMENT_PENALTY
            "Enter effect",                    // MSG_ENTER_EFFECT - 40
            "Enter duration",                  // MSG_ENTER_DURATION
            "Enter use time",                  // MSG_ENTER_USE_TIME
            "Enter charges",                   // MSG_ENTER_CHARGES
            "Enter quest ID",                  // MSG_ENTER_QUEST_ID
            "Enter story",                     // MSG_ENTER_STORY
            "Enter harvest location",          // MSG_ENTER_HARVEST_LOCATION
            "Select language",                 // MSG_SELECT_LANGUAGE
            "Inventory is empty",              // MSG_INVENTORY_EMPTY
            "Weapon",                          // MSG_WEAPON
            "Armor",                           // MSG_ARMOR - 50
            "Consumable",                      // MSG_CONSUMABLE
            "Quest Item",                      // MSG_QUEST_ITEM
            "Material",                        // MSG_MATERIAL
            "Worthless",                       // MSG_WORTHLESS
            "Common",                          // MSG_COMMON
            "Rare",                            // MSG_RARE
            "Epic",                            // MSG_EPIC
            "Legendary",                       // MSG_LEGENDARY
            "Mythic",                          // MSG_MYTHIC
            "Divine",                          // MSG_DIVINE - 60
            "New",                             // MSG_NEW
            "Worn",                            // MSG_WORN
            "Broken",                          // MSG_BROKEN
            "Cursed",                          // MSG_CURSED
            "Select an option",                // MSG_SELECT_OPTION
            "Your choice: ",                   // MSG_YOUR_CHOICE
            "Item name",                       // MSG_ITEM_NAME
            "Type",                            // MSG_ITEM_TYPE
            "Rarity",                          // MSG_ITEM_RARITY
            "State",                           // MSG_ITEM_STATE - 70
            "Description",                     // MSG_ITEM_DESCRIPTION
            "Weight",                          // MSG_ITEM_WEIGHT
            "Value",                           // MSG_ITEM_VALUE
            "Passive effect",                  // MSG_ITEM_PASSIVE_EFFECT
            "Min damage",                      // MSG_ITEM_MIN_DAMAGE
            "Max damage",                      // MSG_ITEM_MAX_DAMAGE
            "Damage type",                     // MSG_ITEM_DAMAGE_TYPE
            "Durability",                      // MSG_ITEM_DURABILITY
            "Range",                           // MSG_ITEM_RANGE
            "Attack speed",                    // MSG_ITEM_ATTACK_SPEED - 80
            "Defense",                         // MSG_ITEM_DEFENSE
            "Resistances",                     // MSG_ITEM_RESISTANCES
            "Slot",                            // MSG_ITEM_SLOT
            "Movement penalty",                // MSG_ITEM_MOVEMENT_PENALTY
            "Effect",                          // MSG_ITEM_EFFECT
            "Duration",                        // MSG_ITEM_DURATION
            "Use time",                        // MSG_ITEM_USE_TIME
            "Charges",                         // MSG_ITEM_CHARGES
            "Quest ID",                        // MSG_ITEM_QUEST_ID
            "Story",                           // MSG_ITEM_STORY - 90
            "Harvest location",                // MSG_ITEM_HARVEST_LOCATION
            "Head",                            // MSG_HEAD
            "Chest",                           // MSG_CHEST
            "Legs",                            // MSG_LEGS
            "Hands",                           // MSG_HANDS
            "Off-hand",                        // MSG_OFFHAND
            "Inventory full! Item discarded.",  // MSG_INVENTORY_FULL
            "Total Weight",                    // MSG_ACTUAL_BAG_WEIGHT
            "Wallet",                          // MSG_WALLET
            "Enter item name (French)",        // MSG_ENTER_NAME_FR - 100
            "Enter item description (French)", // MSG_ENTER_DESCRIPTION_FR
            "Enter passive effect (French)",   // MSG_ENTER_PASSIVE_EFFECT_FR
            "Enter damage type (French)",      // MSG_ENTER_DAMAGE_TYPE_FR
            "Enter resistances (French)",      // MSG_ENTER_RESISTANCES_FR
            "Enter effect (French)",           // MSG_ENTER_EFFECT_FR
            "Enter story (French)",            // MSG_ENTER_STORY_FR
            "Enter harvest location (French)",  // MSG_ENTER_HARVEST_LOCATION_FR
            "Not enough PHGold!",              // MSG_NOT_ENOUGH_GOLD
            "Sell items",                       // MSG_SELL_ITEMS
            "Item sold"                        // MSG_ITEM_SOLD - 110
        },
        // French
        {
            "=== Système de gestion d'inventaire ===", // MSG_MENU_TITLE
            "Partir à l'aventure",                    // MSG_ADVENTURE
            "Visiter la boutique",                    // MSG_SHOP
            "Parcourir l'inventaire",                 // MSG_BROWSE
            "Paramètres",                             // MSG_SETTINGS
            "Paramètres actuels",                     // MSG_ACTUAL_SETTINGS
            "Crédits",                                // MSG_CREDITS
            "Quitter",                                // MSG_QUIT
            "Choix inattendu.",                       // MSG_INVALID_CHOICE
            "Changer la langue",                      // MSG_CHANGE_LANGUAGE
            "Changer le poids maximum",               // MSG_CHANGE_MAX_WEIGHT
            "Poids maximum actuel",                   // MSG_ACTUAL_MAX_WEIGHT
            "Ajouter un objet",                       // MSG_ADD_ITEM
            "Retour",                                 // MSG_BACK
            "Anglais",                                // MSG_ENGLISH
            "Français",                               // MSG_FRENCH
            "Langue mise à jour.",                    // MSG_LANGUAGE_UPDATED
            "Poids maximum mis à jour à",             // MSG_MAX_WEIGHT_UPDATED
            "Poids invalide.",                        // MSG_INVALID_WEIGHT
            "Objet créé : ",                          // MSG_ITEM_CREATED
            "Échec de la création de l'objet.",       // MSG_FAILED_TO_CREATE_ITEM
            "Entrez le nom de l'objet",               // MSG_ENTER_ITEM_NAME
            "Sélectionnez le type d'objet",           // MSG_SELECT_ITEM_TYPE
            "Sélectionnez la rareté de l'objet",      // MSG_SELECT_ITEM_RARITY
            "Sélectionnez l'état de l'objet",         // MSG_SELECT_ITEM_STATE
            "Entrez la description de l'objet",       // MSG_ENTER_ITEM_DESCRIPTION
            "Entrez le poids de l'objet",             // MSG_ENTER_ITEM_WEIGHT
            "Entrez la valeur de l'objet",            // MSG_ENTER_ITEM_VALUE
            "Entrez l'effet passif",                  // MSG_ENTER_PASSIVE_EFFECT
            "Entrez les dégâts minimum",              // MSG_ENTER_MIN_DAMAGE
            "Entrez les dégâts maximum",              // MSG_ENTER_MAX_DAMAGE
            "Entrez le type de dégâts",               // MSG_ENTER_DAMAGE_TYPE
            "Entrez la durabilité",                   // MSG_ENTER_DURABILITY
            "Entrez la portée",                       // MSG_ENTER_RANGE
            "Entrez la vitesse d'attaque",            // MSG_ENTER_ATTACK_SPEED
            "Entrez la défense",                      // MSG_ENTER_DEFENSE
            "Entrez les résistances",                 // MSG_ENTER_RESISTANCES
            "Sélectionnez l'emplacement",             // MSG_SELECT_SLOT
            "Entrez la pénalité de mouvement",        // MSG_ENTER_MOVEMENT_PENALTY
            "Entrez l'effet",                         // MSG_ENTER_EFFECT
            "Entrez la durée",                        // MSG_ENTER_DURATION
            "Entrez le temps d'utilisation",          // MSG_ENTER_USE_TIME
            "Entrez le nombre de charges",            // MSG_ENTER_CHARGES
            "Entrez l'ID de la quête",                // MSG_ENTER_QUEST_ID
            "Entrez l'histoire",                      // MSG_ENTER_STORY
            "Entrez le lieu de récolte",              // MSG_ENTER_HARVEST_LOCATION
            "Choisir la langue",                      // MSG_SELECT_LANGUAGE
            "L'inventaire est vide",                  // MSG_INVENTORY_EMPTY
            "Arme",                                   // MSG_WEAPON
            "Armure",                                 // MSG_ARMOR
            "Consommable",                            // MSG_CONSUMABLE
            "Objet de quête",                         // MSG_QUEST_ITEM
            "Matériau",                               // MSG_MATERIAL
            "Sans valeur",                            // MSG_WORTHLESS
            "Commun",                                 // MSG_COMMON
            "Rare",                                   // MSG_RARE
            "Épique",                                 // MSG_EPIC
            "Légendaire",                             // MSG_LEGENDARY
            "Mythique",                               // MSG_MYTHIC
            "Divin",                                  // MSG_DIVINE
            "Neuf",                                   // MSG_NEW
            "Usé",                                    // MSG_WORN
            "Cassé",                                  // MSG_BROKEN
            "Maudit",                                 // MSG_CURSED
            "Choisissez une option",                  // MSG_SELECT_OPTION
            "Votre choix : ",                         // MSG_YOUR_CHOICE
            "Nom de l’objet",                         // MSG_ITEM_NAME
            "Type",                                   // MSG_ITEM_TYPE
            "Rareté",                                 // MSG_ITEM_RARITY
            "État",                                   // MSG_ITEM_STATE
            "Description",                            // MSG_ITEM_DESCRIPTION
            "Poids",                                  // MSG_ITEM_WEIGHT
            "Valeur",                                 // MSG_ITEM_VALUE
            "Effet passif",                           // MSG_ITEM_PASSIVE_EFFECT
            "Dégâts minimum",                         // MSG_ITEM_MIN_DAMAGE
            "Dégâts maximum",                         // MSG_ITEM_MAX_DAMAGE
            "Type de dégâts",                         // MSG_ITEM_DAMAGE_TYPE
            "Durabilité",                             // MSG_ITEM_DURABILITY
            "Portée",                                 // MSG_ITEM_RANGE
            "Vitesse d’attaque",                      // MSG_ITEM_ATTACK_SPEED
            "Défense",                                // MSG_ITEM_DEFENSE
            "Résistances",                            // MSG_ITEM_RESISTANCES
            "Emplacement",                            // MSG_ITEM_SLOT
            "Pénalité de mouvement",                  // MSG_ITEM_MOVEMENT_PENALTY
            "Effet",                                  // MSG_ITEM_EFFECT
            "Durée",                                  // MSG_ITEM_DURATION
            "Temps d’utilisation",                    // MSG_ITEM_USE_TIME
            "Charges",                                // MSG_ITEM_CHARGES
            "ID de quête",                            // MSG_ITEM_QUEST_ID
            "Histoire",                               // MSG_ITEM_STORY
            "Lieu de récolte",                        // MSG_ITEM_HARVEST_LOCATION
            "Tête",                                   // MSG_HEAD
            "Torse",                                  // MSG_CHEST
            "Jambes",                                 // MSG_LEGS
            "Mains",                                  // MSG_HANDS
            "Main secondaire",                        // MSG_OFFHAND
            "Inventaire plein ! Objet rejeté.",       // MSG_INVENTORY_FULL
            "Poids total",                            // MSG_ACTUAL_BAG_WEIGHT
            "Portefeuille",                            // MSG_WALLET
            "Entrez le nom de l'objet (Français)", // MSG_ENTER_NAME_FR
            "Entrez la description de l'objet (Français)", // MSG_ENTER_DESCRIPTION_FR
            "Entrez l'effet passif (Français)", // MSG_ENTER_PASSIVE_EFFECT_FR
            "Entrez le type de dégâts (Français)", // MSG_ENTER_DAMAGE_TYPE_FR
            "Entrez les résistances (Français)", // MSG_ENTER_RESISTANCES_FR
            "Entrez l'effet (Français)",       // MSG_ENTER_EFFECT_FR
            "Entrez l'histoire (Français)",    // MSG_ENTER_STORY_FR
            "Entrez le lieu de récolte (Français)", // MSG_ENTER_HARVEST_LOCATION_FR
            "Pas assez de PHGold !",                // MSG_NOT_ENOUGH_GOLD
            "Vendre des items",                 // MSG_SELL_ITEMS
            "Item vendu"                       // MSG_ITEM_SOLD
        }
    };

    if (language != GAME_LANG_ENGLISH && language != GAME_LANG_FRENCH) {
        return "Invalid language";
    }
    if (message_id < 0 || message_id >= 110) {
        return "Invalid message ID";
    }

    return messages[language][message_id];
}

// Displays credits
void display_credits(int language) {
    static const char* credits[2] = {
        "Dedicated to my beloved wife and son, whose patience and love inspire me every day.\n\n-- Press any key to continue... --\n",
        "Dédié à ma femme et mon fils adorés, dont la patience et l’amour m’inspirent chaque jour.\n\n-- Appuyez sur une touche pour continuer... --\n"
    };
    printf("\n=== %s ===\n\n", get_message(MSG_CREDITS, language));
    printf("%s\n", credits[language]);
}

// Utility function to display a menu
static int get_menu_choice(int prompt_id, const int options[], int num_options, int language) {
    int choice;
    printf("\n%s:\n\n", get_message(prompt_id, language));
    for (int i = 0; i < num_options; i++) {
        printf("%d. %s\n", i + 1, get_message(options[i], language));
    }
    while (1) {
        printf("\n%s: ", get_message(MSG_YOUR_CHOICE, language)); // Prompt neutre
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("%s (1-%d)\n", get_message(MSG_INVALID_CHOICE, language), num_options);
            continue;
        }
        clear_input_buffer();
        if (choice >= 1 && choice <= num_options) {
            break;
        }
        printf("%s (1-%d)\n", get_message(MSG_INVALID_CHOICE, language), num_options);
    }
    return choice - 1; // Retourner l'indice (0-based)
}

// Fonction pour configurer les paramètres
void configure_settings(GameSettings* settings, Inventory* inv, ItemDatabase* db) {
    if (!settings || !inv || !db) {
        printf("Error: Invalid settings, inventory, or database pointer.\n");
        return;
    }

    int keep_running = 1;
    const int menu_options[] = {
        MSG_CHANGE_LANGUAGE,
        MSG_CHANGE_MAX_WEIGHT,
        MSG_ADD_ITEM,
        MSG_BACK
    };
    const int num_options = 4;

    while (keep_running) {
        printf("\n=== %s ===\n\n", get_message(MSG_SETTINGS, settings->language));
        printf("%s: %s\n", get_message(MSG_ACTUAL_SETTINGS, settings->language),
               settings->language == GAME_LANG_ENGLISH ? "English" : "French");
        printf("%s: %.2f Kg\n", get_message(MSG_ACTUAL_MAX_WEIGHT, settings->language),
               settings->max_weight);

        int choice = get_menu_choice(MSG_SELECT_OPTION, menu_options, num_options, settings->language);

        switch (choice) {
            case 0: {
                const int lang_options[] = {MSG_ENGLISH, MSG_FRENCH};
                int lang_choice = get_menu_choice(MSG_SELECT_LANGUAGE, lang_options, 2, settings->language);
                settings->language = lang_choice;
                printf("\n/!\\ %s /!\\\n", get_message(MSG_LANGUAGE_UPDATED, settings->language));
                break;
            }
            case 1: {
                printf("\n%s: ", get_message(MSG_CHANGE_MAX_WEIGHT, settings->language));
                float new_weight;
                scanf("%f", &new_weight);
                clear_input_buffer();
                if (new_weight >= 0) {
                    settings->max_weight = new_weight;
                    inv->max_weight = new_weight;
                    printf("\n/!\\ %s %.2f Kg /!\\\n", get_message(MSG_MAX_WEIGHT_UPDATED, settings->language), new_weight);
                } else {
                    printf("%s\n", get_message(MSG_INVALID_WEIGHT, settings->language));
                }
                break;
            }
            case 2: {
                Item* new_item = create_item_from_menu(settings->language, db);
                if (new_item) {
                    //add_item(inv, new_item, settings->language);
                    printf("\n/!\\ %s%s /!\\\n", get_message(MSG_ITEM_CREATED, settings->language),
                           settings->language == GAME_LANG_ENGLISH ? new_item->name_en : new_item->name_fr);
                } else {
                    printf("%s\n", get_message(MSG_FAILED_TO_CREATE_ITEM, settings->language));
                }
                break;
            }
            case 3: {
                printf("\n%s\n", get_message(MSG_BACK, settings->language));
                keep_running = 0;
                break;
            }
        }
    }
}

// Fonction pour créer un objet via un menu interactif
Item* create_item_from_menu(int language, ItemDatabase* db) {
    char name_en[50], name_fr[50], description_en[100], description_fr[100], passive_effect_en[50], passive_effect_fr[50];
    float weight;
    int value;
    int type, rarity, state;

    const int type_options[] = {MSG_WEAPON, MSG_ARMOR, MSG_CONSUMABLE, MSG_QUEST_ITEM, MSG_MATERIAL};
    const int rarity_options[] = {MSG_WORTHLESS, MSG_COMMON, MSG_RARE, MSG_EPIC, MSG_LEGENDARY, MSG_MYTHIC, MSG_DIVINE};
    const int state_options[] = {MSG_NEW, MSG_WORN, MSG_BROKEN, MSG_CURSED};
    const int slot_options[] = {MSG_HEAD, MSG_CHEST, MSG_LEGS, MSG_HANDS, MSG_OFFHAND};

    printf("\n=== %s ===\n", get_message(MSG_ADD_ITEM, language));
    printf("\n%s: ", get_message(MSG_ENTER_ITEM_NAME, language));
    while (1) {
        fgets(name_en, sizeof(name_en), stdin);
        name_en[strcspn(name_en, "\n")] = '\0';
        if (strlen(name_en) > 0) break;
        printf("%s: ", get_message(MSG_ENTER_ITEM_NAME, language));
    }
    printf("%s: ", get_message(MSG_ENTER_NAME_FR, language));
    while (1) {
        fgets(name_fr, sizeof(name_fr), stdin);
        name_fr[strcspn(name_fr, "\n")] = '\0';
        if (strlen(name_fr) > 0) break;
        printf("%s: ", get_message(MSG_ENTER_NAME_FR, language));
    }

    type = get_menu_choice(MSG_SELECT_ITEM_TYPE, type_options, 5, language);
    rarity = get_menu_choice(MSG_SELECT_ITEM_RARITY, rarity_options, 7, language);
    if (rarity < 0 || rarity > 6) {
        printf("%s\n", get_message(MSG_FAILED_TO_CREATE_ITEM, language));
        return NULL;
    }
    state = get_menu_choice(MSG_SELECT_ITEM_STATE, state_options, 4, language);

    printf("\n%s: ", get_message(MSG_ENTER_ITEM_DESCRIPTION, language));
    fgets(description_en, sizeof(description_en), stdin);
    description_en[strcspn(description_en, "\n")] = '\0';
    printf("%s: ", get_message(MSG_ENTER_DESCRIPTION_FR, language));
    fgets(description_fr, sizeof(description_fr), stdin);
    description_fr[strcspn(description_fr, "\n")] = '\0';

    printf("%s: ", get_message(MSG_ENTER_ITEM_WEIGHT, language));
    scanf("%f", &weight);
    clear_input_buffer();

    printf("%s: ", get_message(MSG_ENTER_ITEM_VALUE, language));
    scanf("%d", &value);
    clear_input_buffer();

    printf("%s: ", get_message(MSG_ENTER_PASSIVE_EFFECT, language));
    fgets(passive_effect_en, sizeof(passive_effect_en), stdin);
    passive_effect_en[strcspn(passive_effect_en, "\n")] = '\0';
    printf("%s: ", get_message(MSG_ENTER_PASSIVE_EFFECT_FR, language));
    fgets(passive_effect_fr, sizeof(passive_effect_fr), stdin);
    passive_effect_fr[strcspn(passive_effect_fr, "\n")] = '\0';

    void* specific_data = NULL;
    switch (type) {
        case TYPE_WEAPON: {
            Weapon weapon = {0};
            printf("%s: ", get_message(MSG_ENTER_MIN_DAMAGE, language));
            scanf("%d", &weapon.min_damage);
            printf("%s: ", get_message(MSG_ENTER_MAX_DAMAGE, language));
            scanf("%d", &weapon.max_damage);
            printf("%s: ", get_message(MSG_ENTER_DAMAGE_TYPE, language));
            clear_input_buffer();
            fgets(weapon.damage_type_en, sizeof(weapon.damage_type_en), stdin);
            weapon.damage_type_en[strcspn(weapon.damage_type_en, "\n")] = '\0';
            printf("%s: ", get_message(MSG_ENTER_DAMAGE_TYPE_FR, language));
            fgets(weapon.damage_type_fr, sizeof(weapon.damage_type_fr), stdin);
            weapon.damage_type_fr[strcspn(weapon.damage_type_fr, "\n")] = '\0';
            printf("%s: ", get_message(MSG_ENTER_DURABILITY, language));
            scanf("%d", &weapon.durability);
            printf("%s: ", get_message(MSG_ENTER_RANGE, language));
            scanf("%f", &weapon.range);
            printf("%s: ", get_message(MSG_ENTER_ATTACK_SPEED, language));
            scanf("%f", &weapon.attack_speed);
            clear_input_buffer();
            specific_data = malloc(sizeof(Weapon));
            if (!specific_data) return NULL;
            *(Weapon*)specific_data = weapon;
            break;
        }
        case TYPE_ARMOR: {
            Armor armor = {0};
            printf("%s: ", get_message(MSG_ENTER_DEFENSE, language));
            scanf("%d", &armor.defense);
            printf("%s: ", get_message(MSG_ENTER_RESISTANCES, language));
            clear_input_buffer();
            fgets(armor.resistances_en, sizeof(armor.resistances_en), stdin);
            armor.resistances_en[strcspn(armor.resistances_en, "\n")] = '\0';
            printf("%s: ", get_message(MSG_ENTER_RESISTANCES_FR, language));
            fgets(armor.resistances_fr, sizeof(armor.resistances_fr), stdin);
            armor.resistances_fr[strcspn(armor.resistances_fr, "\n")] = '\0';
            armor.slot = get_menu_choice(MSG_SELECT_SLOT, slot_options, 5, language);
            printf("%s: ", get_message(MSG_ENTER_MOVEMENT_PENALTY, language));
            scanf("%f", &armor.movement_penalty);
            clear_input_buffer();
            specific_data = malloc(sizeof(Armor));
            if (!specific_data) return NULL;
            *(Armor*)specific_data = armor;
            break;
        }
        case TYPE_CONSUMABLE: {
            Consumable consumable = {0};
            printf("%s: ", get_message(MSG_ENTER_EFFECT, language));
            clear_input_buffer();
            fgets(consumable.effect_en, sizeof(consumable.effect_en), stdin);
            consumable.effect_en[strcspn(consumable.effect_en, "\n")] = '\0';
            printf("%s: ", get_message(MSG_ENTER_EFFECT_FR, language));
            fgets(consumable.effect_fr, sizeof(consumable.effect_fr), stdin);
            consumable.effect_fr[strcspn(consumable.effect_fr, "\n")] = '\0';
            printf("%s: ", get_message(MSG_ENTER_DURATION, language));
            scanf("%d", &consumable.duration);
            printf("%s: ", get_message(MSG_ENTER_USE_TIME, language));
            scanf("%f", &consumable.use_time);
            printf("%s: ", get_message(MSG_ENTER_CHARGES, language));
            scanf("%d", &consumable.charges);
            clear_input_buffer();
            specific_data = malloc(sizeof(Consumable));
            if (!specific_data) return NULL;
            *(Consumable*)specific_data = consumable;
            break;
        }
        case TYPE_QUEST: {
            QuestItem quest = {0};
            printf("%s: ", get_message(MSG_ENTER_QUEST_ID, language));
            clear_input_buffer();
            fgets(quest.quest_id, sizeof(quest.quest_id), stdin);
            quest.quest_id[strcspn(quest.quest_id, "\n")] = '\0';
            printf("%s: ", get_message(MSG_ENTER_STORY, language));
            fgets(quest.story_en, sizeof(quest.story_en), stdin);
            quest.story_en[strcspn(quest.story_en, "\n")] = '\0';
            printf("%s: ", get_message(MSG_ENTER_STORY_FR, language));
            fgets(quest.story_fr, sizeof(quest.story_fr), stdin);
            quest.story_fr[strcspn(quest.story_fr, "\n")] = '\0';
            specific_data = malloc(sizeof(QuestItem));
            if (!specific_data) return NULL;
            *(QuestItem*)specific_data = quest;
            break;
        }
        case TYPE_MATERIAL: {
            Material material = {0};
            printf("%s: ", get_message(MSG_ENTER_HARVEST_LOCATION, language));
            clear_input_buffer();
            fgets(material.harvest_location_en, sizeof(material.harvest_location_en), stdin);
            material.harvest_location_en[strcspn(material.harvest_location_en, "\n")] = '\0';
            printf("%s: ", get_message(MSG_ENTER_HARVEST_LOCATION_FR, language));
            fgets(material.harvest_location_fr, sizeof(material.harvest_location_fr), stdin);
            material.harvest_location_fr[strcspn(material.harvest_location_fr, "\n")] = '\0';
            specific_data = malloc(sizeof(Material));
            if (!specific_data) return NULL;
            *(Material*)specific_data = material;
            break;
        }
    }

    Item* item = create_item(name_en, name_fr, type, rarity, state, description_en, description_fr,
                             weight, value, passive_effect_en, passive_effect_fr, specific_data);
    if (specific_data) free(specific_data);
    if (item && db) {
        add_item_to_database(db, item);
        save_single_item(item, "items.txt"); // Sauvegarder l'item dans items.txt
    }
    return item;
}