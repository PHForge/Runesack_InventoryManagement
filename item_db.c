#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "inventory.h"
#include "utils.h"

#define INITIAL_DB_CAPACITY 10

// Creates an empty item database
ItemDatabase* create_item_database(int capacity) {
    ItemDatabase* db = malloc(sizeof(ItemDatabase));
    if (db) {
        db->items = malloc(capacity * sizeof(Item*));
        db->count = 0;
        db->capacity = capacity;
        if (!db->items) {
            free(db);
            return NULL;
        }
    }
    return db;
}

// Adds an item to the database
void add_item_to_database(ItemDatabase* db, Item* item) {
    if (!db || !item) return;
    if (db->count >= db->capacity) {
        db->capacity *= 2;
        Item** new_items = realloc(db->items, db->capacity * sizeof(Item*));
        if (!new_items) return;
        db->items = new_items;
    }
    db->items[db->count++] = item;
}

// Loads items from a file
// Loads items from a file
ItemDatabase* load_items(const char* filename, int language) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("%s: %s\n", get_message(MSG_FAILED_TO_CREATE_ITEM, language), filename);
        return NULL;
    }

    ItemDatabase* db = create_item_database(INITIAL_DB_CAPACITY);
    if (!db) {
        fclose(file);
        return NULL;
    }

    char line[256];
    Item* item = NULL;
    char name_en[50] = "", name_fr[50] = "";
    char description_en[100] = "", description_fr[100] = "";
    char passive_effect_en[50] = "", passive_effect_fr[50] = "";
    int type = -1, rarity = -1, state = -1, value = 0;
    float weight = 0.0f;

    // Structures pour les types spécifiques
    Weapon weapon = {0};
    Armor armor = {0};
    Consumable consumable = {0};
    QuestItem quest = {0};
    Material material = {0};

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Supprimer le '\n' final
        if (strcmp(line, "ITEM") == 0) {
            // Si un item est en cours de construction, l'ajouter à la base
            if (item) {
                add_item_to_database(db, item);
                item = NULL;
            }
            // Réinitialiser toutes les variables pour le prochain item
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
            // Réinitialiser les structures spécifiques
            memset(&weapon, 0, sizeof(Weapon));
            memset(&armor, 0, sizeof(Armor));
            memset(&consumable, 0, sizeof(Consumable));
            memset(&quest, 0, sizeof(QuestItem));
            memset(&material, 0, sizeof(Material));
            continue;
        }

        // Parser la ligne en clé et valeur
        char* key = strtok(line, ":");
        char* value_str = strtok(NULL, "");
        if (!key || !value_str) continue;
        while (*value_str == ' ') value_str++; // Supprimer les espaces en début de valeur

        // Propriétés communes à tous les items
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
        // Propriétés spécifiques pour TYPE_WEAPON
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
        // Propriétés spécifiques pour TYPE_ARMOR
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
        // Propriétés spécifiques pour TYPE_CONSUMABLE
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
        // Propriétés spécifiques pour TYPE_QUEST
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
        // Propriétés spécifiques pour TYPE_MATERIAL
        else if (type == TYPE_MATERIAL) {
            if (strcmp(key, "harvest_location_en") == 0) {
                strncpy(material.harvest_location_en, value_str, sizeof(material.harvest_location_en) - 1);
                material.harvest_location_en[sizeof(material.harvest_location_en) - 1] = '\0';
            } else if (strcmp(key, "harvest_location_fr") == 0) {
                strncpy(material.harvest_location_fr, value_str, sizeof(material.harvest_location_fr) - 1);
                material.harvest_location_fr[sizeof(material.harvest_location_fr) - 1] = '\0';
            }
        }

        // Vérification et création de l'item selon le type
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

    // Ajouter le dernier item s'il existe
    if (item) {
        add_item_to_database(db, item);
    }

    fclose(file);
    return db;
}

// Saves items to a file
void save_items(ItemDatabase* db, const char* filename) {
    if (!db) return;

    FILE* file = fopen(filename, "a"); // Append mode
    if (!file) return;

    for (int i = 0; i < db->count; i++) {
        Item* item = db->items[i];
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
    }

    fclose(file);
}

// Frees the item database
void free_item_database(ItemDatabase* db) {
    if (!db) return;
    for (int i = 0; i < db->count; i++) {
        free_item(db->items[i]);
    }
    free(db->items);
    free(db);
}

// Loads inventory from a file
void load_inventory(Inventory* inv, const char* filename, ItemDatabase* db, int language) {
    if (!inv || !db) return;

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("%s: %s\n", get_message(MSG_FAILED_TO_CREATE_ITEM, language), filename);
        return;
    }

    char line[256];
    char name_en[50];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        char* key = strtok(line, ":");
        char* value = strtok(NULL, "");
        if (!key || !value) continue;
        while (*value == ' ') value++;

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

    FILE* file = fopen(filename, "w"); // Write mode
    if (!file) return;

    fprintf(file, "phgold: %d\n", inv->phgold);
    fprintf(file, "max_weight: %.2f\n", inv->max_weight);

    InventoryNode* current = inv->head;
    while (current) {
        fprintf(file, "ITEM\n");
        fprintf(file, "name_en: %s\n", current->item->name_en);
        current = current->next;
    }

    fclose(file);
}