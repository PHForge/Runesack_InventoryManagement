#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include "utils.h"

// Creates a new item
Item* create_item(
    const char* name_en, const char* name_fr, int type, int rarity, int state,
    const char* description_en, const char* description_fr, float weight, int value,
    const char* passive_effect_en, const char* passive_effect_fr, void* specific_data
) {
    // Parameter validation
    if (!name_en || !name_fr || !description_en || !description_fr ||
        !passive_effect_en || !passive_effect_fr || !specific_data ||
        type < TYPE_WEAPON || type > TYPE_MATERIAL ||
        rarity < RARITY_WORTHLESS || rarity > RARITY_DIVINE ||
        state < STATE_NEW || state > STATE_CURSED ||
        weight < 0 || value < 0) {
        return NULL;
    }

    Item* new_item = (Item*)malloc(sizeof(Item));
    if (!new_item) {
        return NULL;
    }

    // Initialize generic fields
    strncpy(new_item->name_en, name_en, sizeof(new_item->name_en) - 1);
    new_item->name_en[sizeof(new_item->name_en) - 1] = '\0';
    strncpy(new_item->name_fr, name_fr, sizeof(new_item->name_fr) - 1);
    new_item->name_fr[sizeof(new_item->name_fr) - 1] = '\0';
    new_item->properties.type = type;
    new_item->properties.rarity = rarity;
    new_item->properties.state = state;
    strncpy(new_item->description_en, description_en, sizeof(new_item->description_en) - 1);
    new_item->description_en[sizeof(new_item->description_en) - 1] = '\0';
    strncpy(new_item->description_fr, description_fr, sizeof(new_item->description_fr) - 1);
    new_item->description_fr[sizeof(new_item->description_fr) - 1] = '\0';
    new_item->weight = weight;
    new_item->value = value;
    strncpy(new_item->passive_effect_en, passive_effect_en, sizeof(new_item->passive_effect_en) - 1);
    new_item->passive_effect_en[sizeof(new_item->passive_effect_en) - 1] = '\0';
    strncpy(new_item->passive_effect_fr, passive_effect_fr, sizeof(new_item->passive_effect_fr) - 1);
    new_item->passive_effect_fr[sizeof(new_item->passive_effect_fr) - 1] = '\0';

    // Initialize specific fields
    switch (type) {
        case TYPE_WEAPON: {
            Weapon* weapon = (Weapon*)specific_data;
            if (weapon->min_damage < 0 || weapon->max_damage < weapon->min_damage ||
                weapon->durability < 0 || weapon->range < 0 || weapon->attack_speed < 0) {
                free(new_item);
                return NULL;
            }
            new_item->specific.weapon = *weapon;
            break;
        }
        case TYPE_ARMOR: {
            Armor* armor = (Armor*)specific_data;
            if (armor->defense < 0 || armor->movement_penalty < 0 ||
                armor->slot < SLOT_HEAD || armor->slot > SLOT_OFFHAND) {
                free(new_item);
                return NULL;
            }
            new_item->specific.armor = *armor;
            break;
        }
        case TYPE_CONSUMABLE: {
            Consumable* consumable = (Consumable*)specific_data;
            if (consumable->duration < 0 || consumable->use_time < 0 || consumable->charges < 0) {
                free(new_item);
                return NULL;
            }
            new_item->specific.consumable = *consumable;
            break;
        }
        case TYPE_QUEST: {
            QuestItem* quest = (QuestItem*)specific_data;
            new_item->specific.quest = *quest;
            break;
        }
        case TYPE_MATERIAL: {
            Material* material = (Material*)specific_data;
            new_item->specific.material = *material;
            break;
        }
        default:
            free(new_item);
            return NULL;
    }

    return new_item;
}

// Function to release an object
void free_item(Item* item) {
    if (item) {
        free(item);
    }
}

void print_item(const Item* item, int language) {
    if (!item) {
        printf("%s\n", get_message(MSG_FAILED_TO_CREATE_ITEM, language));
        return;
    }

    printf("%s: %s\n", get_message(MSG_ITEM_NAME, language),
           language == GAME_LANG_ENGLISH ? item->name_en : item->name_fr);
    printf("%s: ", get_message(MSG_ITEM_TYPE, language));
    switch (item->properties.type) {
        case TYPE_WEAPON: printf("%s\n", get_message(MSG_WEAPON, language)); break;
        case TYPE_ARMOR: printf("%s\n", get_message(MSG_ARMOR, language)); break;
        case TYPE_CONSUMABLE: printf("%s\n", get_message(MSG_CONSUMABLE, language)); break;
        case TYPE_QUEST: printf("%s\n", get_message(MSG_QUEST_ITEM, language)); break;
        case TYPE_MATERIAL: printf("%s\n", get_message(MSG_MATERIAL, language)); break;
    }
    printf("%s: ", get_message(MSG_ITEM_RARITY, language));
    switch (item->properties.rarity) {
        case RARITY_WORTHLESS: printf("%s\n", get_message(MSG_WORTHLESS, language)); break;
        case RARITY_COMMON: printf("%s\n", get_message(MSG_COMMON, language)); break;
        case RARITY_RARE: printf("%s\n", get_message(MSG_RARE, language)); break;
        case RARITY_EPIC: printf("%s\n", get_message(MSG_EPIC, language)); break;
        case RARITY_LEGENDARY: printf("%s\n", get_message(MSG_LEGENDARY, language)); break;
        case RARITY_MYTHIC: printf("%s\n", get_message(MSG_MYTHIC, language)); break;
        case RARITY_DIVINE: printf("%s\n", get_message(MSG_DIVINE, language)); break;
    }
    printf("%s: ", get_message(MSG_ITEM_STATE, language));
    switch (item->properties.state) {
        case STATE_NEW: printf("%s\n", get_message(MSG_NEW, language)); break;
        case STATE_WORN: printf("%s\n", get_message(MSG_WORN, language)); break;
        case STATE_BROKEN: printf("%s\n", get_message(MSG_BROKEN, language)); break;
        case STATE_CURSED: printf("%s\n", get_message(MSG_CURSED, language)); break;
    }
    printf("%s: %s\n", get_message(MSG_ITEM_DESCRIPTION, language),
           language == GAME_LANG_ENGLISH ? item->description_en : item->description_fr);
    printf("%s: %.2f Kg\n", get_message(MSG_ITEM_WEIGHT, language), item->weight);
    printf("%s: %d PHGold\n", get_message(MSG_ITEM_VALUE, language), item->value);
    printf("%s: %s\n", get_message(MSG_ITEM_PASSIVE_EFFECT, language),
           language == GAME_LANG_ENGLISH ? item->passive_effect_en : item->passive_effect_fr);

    switch (item->properties.type) {
        case TYPE_WEAPON:
            printf("%s: %d\n", get_message(MSG_ITEM_MIN_DAMAGE, language), item->specific.weapon.min_damage);
            printf("%s: %d\n", get_message(MSG_ITEM_MAX_DAMAGE, language), item->specific.weapon.max_damage);
            printf("%s: %s\n", get_message(MSG_ITEM_DAMAGE_TYPE, language),
                   language == GAME_LANG_ENGLISH ? item->specific.weapon.damage_type_en : item->specific.weapon.damage_type_fr);
            printf("%s: %d%%\n", get_message(MSG_ITEM_DURABILITY, language), item->specific.weapon.durability);
            printf("%s: %.2f m\n", get_message(MSG_ITEM_RANGE, language), item->specific.weapon.range);
            printf("%s: %.2f\n", get_message(MSG_ITEM_ATTACK_SPEED, language), item->specific.weapon.attack_speed);
            break;
        case TYPE_ARMOR:
            printf("%s: %d\n", get_message(MSG_ITEM_DEFENSE, language), item->specific.armor.defense);
            printf("%s: %s\n", get_message(MSG_ITEM_RESISTANCES, language),
                   language == GAME_LANG_ENGLISH ? item->specific.armor.resistances_en : item->specific.armor.resistances_fr);
            printf("%s: ", get_message(MSG_ITEM_SLOT, language));
            switch (item->specific.armor.slot) {
                case SLOT_HEAD: printf("%s\n", get_message(MSG_HEAD, language)); break;
                case SLOT_CHEST: printf("%s\n", get_message(MSG_CHEST, language)); break;
                case SLOT_LEGS: printf("%s\n", get_message(MSG_LEGS, language)); break;
                case SLOT_HANDS: printf("%s\n", get_message(MSG_HANDS, language)); break;
                case SLOT_OFFHAND: printf("%s\n", get_message(MSG_OFFHAND, language)); break;
            }
            printf("%s: %.2f\n", get_message(MSG_ITEM_MOVEMENT_PENALTY, language), item->specific.armor.movement_penalty);
            break;
        case TYPE_CONSUMABLE:
            printf("%s: %s\n", get_message(MSG_ITEM_EFFECT, language),
                   language == GAME_LANG_ENGLISH ? item->specific.consumable.effect_en : item->specific.consumable.effect_fr);
            printf("%s: %d\n", get_message(MSG_ITEM_DURATION, language), item->specific.consumable.duration);
            printf("%s: %.2f\n", get_message(MSG_ITEM_USE_TIME, language), item->specific.consumable.use_time);
            printf("%s: %d\n", get_message(MSG_ITEM_CHARGES, language), item->specific.consumable.charges);
            break;
        case TYPE_QUEST:
            printf("%s: %s\n", get_message(MSG_ITEM_QUEST_ID, language), item->specific.quest.quest_id);
            printf("%s: %s\n", get_message(MSG_ITEM_STORY, language),
                   language == GAME_LANG_ENGLISH ? item->specific.quest.story_en : item->specific.quest.story_fr);
            break;
        case TYPE_MATERIAL:
            printf("%s: %s\n", get_message(MSG_ITEM_HARVEST_LOCATION, language),
                   language == GAME_LANG_ENGLISH ? item->specific.material.harvest_location_en : item->specific.material.harvest_location_fr);
            break;
    }
}