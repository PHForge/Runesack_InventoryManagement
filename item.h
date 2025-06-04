#ifndef ITEM_H
#define ITEM_H

#define TYPE_WEAPON 0
#define TYPE_ARMOR 1
#define TYPE_CONSUMABLE 2
#define TYPE_QUEST 3
#define TYPE_MATERIAL 4

#define RARITY_WORTHLESS 0
#define RARITY_COMMON 1
#define RARITY_RARE 2
#define RARITY_EPIC 3
#define RARITY_LEGENDARY 4
#define RARITY_MYTHIC 5
#define RARITY_DIVINE 6 // DLC with hell to anticipate!

#define STATE_NEW 0
#define STATE_WORN 1
#define STATE_BROKEN 2
#define STATE_CURSED 3

#define SLOT_HEAD 0
#define SLOT_CHEST 1
#define SLOT_LEGS 2
#define SLOT_HANDS 3
#define SLOT_OFFHAND 4

typedef struct {
    unsigned int type : 3;    // Bitmask: 0-4 (5 types)
    unsigned int rarity : 3;  // Bitmask: 0-6 (7 rarities)
    unsigned int state : 2;   // Bitmask: 0-3 (4 states)
} ItemProperties;

typedef struct {
    int min_damage;
    int max_damage;
    char damage_type_en[20];
    char damage_type_fr[20];
    int durability;
    float range;
    float attack_speed;
} Weapon;

typedef struct {
    int defense;
    char resistances_en[50];
    char resistances_fr[50];
    int slot; // 0: Head, 1: Chest, 2: Legs, 3: Hands, 4: Offhand
    float movement_penalty;
} Armor;

typedef struct {
    char effect_en[50];
    char effect_fr[50];
    int duration; // indicates how long the effect of the consumable is active after use
    float use_time; // indicates the time required to activate or consume the item
    int charges;
} Consumable;

typedef struct {
    char quest_id[50];
    char story_en[100];
    char story_fr[100];
} QuestItem;

typedef struct {
    char harvest_location_en[50];
    char harvest_location_fr[50];
} Material;

typedef union {
    Weapon weapon;
    Armor armor;
    Consumable consumable;
    QuestItem quest;
    Material material;
} ItemSpecific;

typedef struct {
    char name_en[50];
    char name_fr[50];
    ItemProperties properties;
    char description_en[100];
    char description_fr[100];
    float weight;
    int value;
    char passive_effect_en[50];
    char passive_effect_fr[50];
    ItemSpecific specific;
} Item;

Item* create_item(const char* name_en, const char* name_fr, int type, int rarity, int state,
                  const char* description_en, const char* description_fr, float weight, int value,
                  const char* passive_effect_en, const char* passive_effect_fr, void* specific_data);
void free_item(Item* item);
void print_item(const Item* item, int language);

// Nouvelle structure pour la base de données
typedef struct {
    Item** items;
    int count;
    int capacity;
} ItemDatabase;

ItemDatabase* load_items(const char* filename, int language);
void save_items(ItemDatabase* db, const char* filename);
void free_item_database(ItemDatabase* db);
ItemDatabase* create_item_database(int capacity);
void add_item_to_database(ItemDatabase* db, Item* item);
void save_single_item(Item* item, const char* filename);


#endif