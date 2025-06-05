#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "inventory.h"
#include "utils.h"

// Initial capacity for the item database
#define INITIAL_DB_CAPACITY 10

// Creates an empty item database
ItemDatabase* create_item_database(int capacity) {
    ItemDatabase* db = malloc(sizeof(ItemDatabase)); // Allocate memory for the database
    if (db) {
        db->items = malloc(capacity * sizeof(Item*)); // Allocate memory for the items array
        db->count = 0; 
        db->capacity = capacity; 
        if (!db->items) { 
            free(db); // Free the database if items allocation fails
            return NULL;
        }
    }
    return db;
}

// Adds an item to the database
void add_item_to_database(ItemDatabase* db, Item* item) {
    if (!db || !item) return; // Check if the database and item are valid
    if (db->count >= db->capacity) { // Check if the database is full
        db->capacity *= 2; 
        Item** new_items = realloc(db->items, db->capacity * sizeof(Item*)); // Resize the items array
        if (!new_items) return; // If resizing fails, do not add the item
        db->items = new_items; // Update the items pointer to the new array
    }
    db->items[db->count++] = item; // Add the item to the database and increment the count
}

// Loads items from a file
ItemDatabase* load_items(const char* filename, int language) {
    FILE* file = fopen(filename, "r"); // Open the file for reading
    if (!file) { // If the file cannot be opened, print an error message
        printf("%s: %s\n", get_message(MSG_FAILED_TO_CREATE_ITEM, language), filename);
        return NULL;
    }

    // Create an empty item database with initial capacity
    ItemDatabase* db = create_item_database(INITIAL_DB_CAPACITY);
    if (!db) {
        fclose(file);
        return NULL;
    }

    char line[256]; // Buffer to read each line from the file
    Item* item = NULL; // Pointer to hold the current item being constructed
    char name_en[50] = "", name_fr[50] = ""; 
    char description_en[100] = "", description_fr[100] = "";
    char passive_effect_en[50] = "", passive_effect_fr[50] = "";
    int type = -1, rarity = -1, state = -1, value = 0;
    float weight = 0.0f;

    // Structures for specific types
    Weapon weapon = {0};
    Armor armor = {0};
    Consumable consumable = {0};
    QuestItem quest = {0};
    Material material = {0};

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove the trailing '\n'
        if (strcmp(line, "ITEM") == 0) {
            // If we encounter a new item, check if we have a complete item to add
            if (item) {
                add_item_to_database(db, item);
                item = NULL;
            }
            // Reset item properties for the new item
            type = -1;
            rarity = -1;
            state = -1;
            name_en[0] = '\0';
            name_fr[0] = '\0';
            description_en[0] = '\0';
            description_fr[0] = '\0';
            passive_effect_en[0] = '\0';
            passive_effect_fr[0] = '\0';
            value = 0;
            weight = 0.0f;
            // Reset specific item properties
            memset(&weapon, 0, sizeof(Weapon));
            memset(&armor, 0, sizeof(Armor));
            memset(&consumable, 0, sizeof(Consumable));
            memset(&quest, 0, sizeof(QuestItem));
            memset(&material, 0, sizeof(Material));
            continue;
        }

        
        char* key = strtok(line, ":"); // Split the line into key and value
        char* value_str = strtok(NULL, ""); // Get the value part after the colon
        if (!key || !value_str) continue; // If the line is not valid, skip it
        while (*value_str == ' ') value_str++; // Skip leading spaces in the value

        // Properties common to all items
        // Check the key and assign the value to the appropriate variable
        if (strcmp(key, "type") == 0) {
            type = atoi(value_str);
            if (type < TYPE_WEAPON || type > TYPE_MATERIAL) type = -1;
        } else if (strcmp(key, "name_en") == 0) {
            strncpy(name_en, value_str, sizeof(name_en) - 1);
            name_en[sizeof(name_en) - 1] = '\0';
        } else if (strcmp(key, "name_fr") == 0) {
            strncpy(name_fr, value_str, sizeof(name_fr) - 1);
            name_fr[sizeof(name_fr) - 1] = '\0';
        } else if (strcmp(key, "rarity") == 0) {
            rarity = atoi(value_str);
            if (rarity < RARITY_WORTHLESS || rarity > RARITY_DIVINE) rarity = -1;
        } else if (strcmp(key, "state") == 0) {
            state = atoi(value_str);
            if (state < STATE_NEW || state > STATE_CURSED) state = -1;
        } else if (strcmp(key, "description_en") == 0) {
            strncpy(description_en, value_str, sizeof(description_en) - 1);
            description_en[sizeof(description_en) - 1] = '\0';
        } else if (strcmp(key, "description_fr") == 0) {
            strncpy(description_fr, value_str, sizeof(description_fr) - 1);
            description_fr[sizeof(description_fr) - 1] = '\0';
        } else if (strcmp(key, "weight") == 0) {
            weight = atof(value_str);
        } else if (strcmp(key, "value") == 0) {
            value = atoi(value_str);
        } else if (strcmp(key, "passive_effect_en") == 0) {
            strncpy(passive_effect_en, value_str, sizeof(passive_effect_en) - 1);
            passive_effect_en[sizeof(passive_effect_en) - 1] = '\0';
        } else if (strcmp(key, "passive_effect_fr") == 0) {
            strncpy(passive_effect_fr, value_str, sizeof(passive_effect_fr) - 1);
            passive_effect_fr[sizeof(passive_effect_fr) - 1] = '\0';
        }
        // Specific properties for TYPE_WEAPON
        // Check if the type is TYPE_WEAPON and assign the specific properties
        else if (type == TYPE_WEAPON) {
            if (strcmp(key, "min_damage") == 0) {
                weapon.min_damage = atoi(value_str);
            } else if (strcmp(key, "max_damage") == 0) {
                weapon.max_damage = atoi(value_str);
            } else if (strcmp(key, "damage_type_en") == 0) {
                strncpy(weapon.damage_type_en, value_str, sizeof(weapon.damage_type_en) - 1);
                weapon.damage_type_en[sizeof(weapon.damage_type_en) - 1] = '\0';
            } else if (strcmp(key, "damage_type_fr") == 0) {
                strncpy(weapon.damage_type_fr, value_str, sizeof(weapon.damage_type_fr) - 1);
                weapon.damage_type_fr[sizeof(weapon.damage_type_fr) - 1] = '\0';
            } else if (strcmp(key, "durability") == 0) {
                weapon.durability = atoi(value_str);
            } else if (strcmp(key, "range") == 0) {
                weapon.range = atof(value_str);
            } else if (strcmp(key, "attack_speed") == 0) {
                weapon.attack_speed = atof(value_str);
            }
        }
        // Specific properties for TYPE_ARMOR
        else if (type == TYPE_ARMOR) {
            if (strcmp(key, "defense") == 0) {
                armor.defense = atoi(value_str);
            } else if (strcmp(key, "resistances_en") == 0) {
                strncpy(armor.resistances_en, value_str, sizeof(armor.resistances_en) - 1);
                armor.resistances_en[sizeof(armor.resistances_en) - 1] = '\0';
            } else if (strcmp(key, "resistances_fr") == 0) {
                strncpy(armor.resistances_fr, value_str, sizeof(armor.resistances_fr) - 1);
                armor.resistances_fr[sizeof(armor.resistances_fr) - 1] = '\0';
            } else if (strcmp(key, "slot") == 0) {
                armor.slot = atoi(value_str);
                if (armor.slot < SLOT_HEAD || armor.slot > SLOT_OFFHAND) armor.slot = SLOT_HEAD;
            } else if (strcmp(key, "movement_penalty") == 0) {
                armor.movement_penalty = atof(value_str);
            }
        }
        // Specific properties for TYPE_CONSUMABLE
        else if (type == TYPE_CONSUMABLE) {
            if (strcmp(key, "effect_en") == 0) {
                strncpy(consumable.effect_en, value_str, sizeof(consumable.effect_en) - 1);
                consumable.effect_en[sizeof(consumable.effect_en) - 1] = '\0';
            } else if (strcmp(key, "effect_fr") == 0) {
                strncpy(consumable.effect_fr, value_str, sizeof(consumable.effect_fr) - 1);
                consumable.effect_fr[sizeof(consumable.effect_fr) - 1] = '\0';
            } else if (strcmp(key, "duration") == 0) {
                consumable.duration = atoi(value_str);
            } else if (strcmp(key, "use_time") == 0) {
                consumable.use_time = atof(value_str);
            } else if (strcmp(key, "charges") == 0) {
                consumable.charges = atoi(value_str);
            }
        }
        // Specific properties for TYPE_QUEST
        else if (type == TYPE_QUEST) {
            if (strcmp(key, "quest_id") == 0) {
                strncpy(quest.quest_id, value_str, sizeof(quest.quest_id) - 1);
                quest.quest_id[sizeof(quest.quest_id) - 1] = '\0';
            } else if (strcmp(key, "story_en") == 0) {
                strncpy(quest.story_en, value_str, sizeof(quest.story_en) - 1);
                quest.story_en[sizeof(quest.story_en) - 1] = '\0';
            } else if (strcmp(key, "story_fr") == 0) {
                strncpy(quest.story_fr, value_str, sizeof(quest.story_fr) - 1);
                quest.story_fr[sizeof(quest.story_fr) - 1] = '\0';
            }
        }
        // Specific properties for TYPE_MATERIAL
        else if (type == TYPE_MATERIAL) {
            if (strcmp(key, "harvest_location_en") == 0) {
                strncpy(material.harvest_location_en, value_str, sizeof(material.harvest_location_en) - 1);
                material.harvest_location_en[sizeof(material.harvest_location_en) - 1] = '\0';
            } else if (strcmp(key, "harvest_location_fr") == 0) {
                strncpy(material.harvest_location_fr, value_str, sizeof(material.harvest_location_fr) - 1);
                material.harvest_location_fr[sizeof(material.harvest_location_fr) - 1] = '\0';
            }
        }

        // If we have all the necessary properties, create the item
        if (name_en[0] && name_fr[0] && type >= 0 && rarity >= 0 && state >= 0) {
            if (type == TYPE_WEAPON &&
                weapon.min_damage >= 0 && weapon.max_damage >= 0 &&
                weapon.damage_type_en[0] && weapon.damage_type_fr[0] &&
                weapon.durability >= 0 && weapon.range >= 0 && weapon.attack_speed >= 0) {
                item = create_item(name_en, name_fr, type, rarity, state,
                                   description_en, description_fr, weight, value,
                                   passive_effect_en, passive_effect_fr, &weapon);
            } else if (type == TYPE_ARMOR &&
                       armor.defense >= 0 && armor.resistances_en[0] &&
                       armor.resistances_fr[0] && armor.slot >= SLOT_HEAD &&
                       armor.slot <= SLOT_OFFHAND) {
                item = create_item(name_en, name_fr, type, rarity, state,
                                   description_en, description_fr, weight, value,
                                   passive_effect_en, passive_effect_fr, &armor);
            } else if (type == TYPE_CONSUMABLE &&
                       consumable.effect_en[0] && consumable.effect_fr[0] &&
                       consumable.duration >= 0 && consumable.use_time >= 0 &&
                       consumable.charges >= 0) {
                item = create_item(name_en, name_fr, type, rarity, state,
                                   description_en, description_fr, weight, value,
                                   passive_effect_en, passive_effect_fr, &consumable);
            } else if (type == TYPE_QUEST &&
                       quest.quest_id[0] && quest.story_en[0] && quest.story_fr[0]) {
                item = create_item(name_en, name_fr, type, rarity, state,
                                   description_en, description_fr, weight, value,
                                   passive_effect_en, passive_effect_fr, &quest);
            } else if (type == TYPE_MATERIAL &&
                       material.harvest_location_en[0] && material.harvest_location_fr[0]) {
                item = create_item(name_en, name_fr, type, rarity, state,
                                   description_en, description_fr, weight, value,
                                   passive_effect_en, passive_effect_fr, &material);
            }
        }
    }

    // Add the last item if it exists
    if (item) {
        add_item_to_database(db, item);
    }

    fclose(file);
    return db; // Return the populated item database
}

// Saves a single item to the file in append mode
void save_single_item(Item* item, const char* filename) {
    if (!item) return; // Check if the item is valid

    FILE* file = fopen(filename, "a"); // Open the file in append mode
    if (!file) return;

    fprintf(file, "ITEM\n");
    fprintf(file, "type: %d\n", item->properties.type);
    fprintf(file, "name_en: %s\n", item->name_en);
    fprintf(file, "name_fr: %s\n", item->name_fr);
    fprintf(file, "rarity: %d\n", item->properties.rarity);
    fprintf(file, "state: %d\n", item->properties.state);
    fprintf(file, "description_en: %s\n", item->description_en);
    fprintf(file, "description_fr: %s\n", item->description_fr);
    fprintf(file, "weight: %.2f\n", item->weight);
    fprintf(file, "value: %d\n", item->value);
    fprintf(file, "passive_effect_en: %s\n", item->passive_effect_en);
    fprintf(file, "passive_effect_fr: %s\n", item->passive_effect_fr);

    // Save specific properties based on the item type
    switch (item->properties.type) {
        case TYPE_WEAPON:
            fprintf(file, "min_damage: %d\n", item->specific.weapon.min_damage);
            fprintf(file, "max_damage: %d\n", item->specific.weapon.max_damage);
            fprintf(file, "damage_type_en: %s\n", item->specific.weapon.damage_type_en);
            fprintf(file, "damage_type_fr: %s\n", item->specific.weapon.damage_type_fr);
            fprintf(file, "durability: %d\n", item->specific.weapon.durability);
            fprintf(file, "range: %.2f\n", item->specific.weapon.range);
            fprintf(file, "attack_speed: %.2f\n", item->specific.weapon.attack_speed);
            break;
        case TYPE_ARMOR:
            fprintf(file, "defense: %d\n", item->specific.armor.defense);
            fprintf(file, "resistances_en: %s\n", item->specific.armor.resistances_en);
            fprintf(file, "resistances_fr: %s\n", item->specific.armor.resistances_fr);
            fprintf(file, "slot: %d\n", item->specific.armor.slot);
            fprintf(file, "movement_penalty: %.2f\n", item->specific.armor.movement_penalty);
            break;
        case TYPE_CONSUMABLE:
            fprintf(file, "effect_en: %s\n", item->specific.consumable.effect_en);
            fprintf(file, "effect_fr: %s\n", item->specific.consumable.effect_fr);
            fprintf(file, "duration: %d\n", item->specific.consumable.duration);
            fprintf(file, "use_time: %.2f\n", item->specific.consumable.use_time);
            fprintf(file, "charges: %d\n", item->specific.consumable.charges);
            break;
        case TYPE_QUEST:
            fprintf(file, "quest_id: %s\n", item->specific.quest.quest_id);
            fprintf(file, "story_en: %s\n", item->specific.quest.story_en);
            fprintf(file, "story_fr: %s\n", item->specific.quest.story_fr);
            break;
        case TYPE_MATERIAL:
            fprintf(file, "harvest_location_en: %s\n", item->specific.material.harvest_location_en);
            fprintf(file, "harvest_location_fr: %s\n", item->specific.material.harvest_location_fr);
            break;
    }

    fclose(file);
}

// Frees the item database
void free_item_database(ItemDatabase* db) {
    if (!db) return;
    for (int i = 0; i < db->count; i++) { // Iterate through each item in the database
        free_item(db->items[i]);
        db->items[i] = NULL; // Set to NULL after freeing to avoid dangling pointers
    }
    free(db->items);
    free(db);
}

// Loads inventory from a file
void load_inventory(Inventory* inv, const char* filename, ItemDatabase* db, int language) {
    if (!inv || !db) return;

    FILE* file = fopen(filename, "r"); // Open the file for reading
    if (!file) {
        printf("%s: %s\n", get_message(MSG_FAILED_TO_CREATE_ITEM, language), filename);
        return;
    }

    char line[256]; // Buffer to read each line from the file
    char name_en[50]; // Buffer to hold the item name in English

    // Initialize inventory properties
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove the trailing '\n'
        char* key = strtok(line, ":"); // Split the line into key and value
        char* value = strtok(NULL, ""); // Get the value part after the colon
        if (!key || !value) continue; // If the line is not valid, skip it
        while (*value == ' ') value++; // Skip leading spaces in the value

        // Check the key and assign the value to the appropriate inventory property
        if (strcmp(key, "phgold") == 0) {
            inv->phgold = atoi(value);
        } else if (strcmp(key, "max_weight") == 0) {
            inv->max_weight = atof(value);
        } else if (strcmp(key, "ITEM") == 0) {
            name_en[0] = '\0';
        } else if (strcmp(key, "name_en") == 0) {
            strncpy(name_en, value, sizeof(name_en) - 1);
            name_en[sizeof(name_en) - 1] = '\0';
            for (int i = 0; i < db->count; i++) { 
                if (strcmp(db->items[i]->name_en, name_en) == 0) {
                    Item* new_item = create_item(
                        db->items[i]->name_en, db->items[i]->name_fr,
                        db->items[i]->properties.type, db->items[i]->properties.rarity,
                        db->items[i]->properties.state, db->items[i]->description_en,
                        db->items[i]->description_fr, db->items[i]->weight,
                        db->items[i]->value, db->items[i]->passive_effect_en,
                        db->items[i]->passive_effect_fr, &db->items[i]->specific);
                    if (new_item) {
                        add_item(inv, new_item, language);
                    }
                    break;
                }
            }
        }
    }

    fclose(file);
}

// Saves inventory to a file
void save_inventory(Inventory* inv, const char* filename) {
    if (!inv) return;

    FILE* file = fopen(filename, "w"); // Open the file for writing
    if (!file) return;

    fprintf(file, "phgold: %d\n", inv->phgold);
    fprintf(file, "max_weight: %.2f\n", inv->max_weight);

    // Iterate through the linked list and save each item
    InventoryNode* current = inv->head; // Start from the head of the linked list
    while (current) {
        fprintf(file, "ITEM\n");
        fprintf(file, "name_en: %s\n", current->item->name_en);
        current = current->next;
    }

    fclose(file);
}