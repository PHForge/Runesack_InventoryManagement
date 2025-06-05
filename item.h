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

// Item properties bitmask definitions
// These definitions allow us to use bitmasks for item properties, making it more memory efficient
typedef struct {
    unsigned int type : 3;    // Bitmask: 0-4 (5 types) // 0: Weapon, 1: Armor, 2: Consumable, 3: Quest Item, 4: Material
    unsigned int rarity : 3;  // Bitmask: 0-6 (7 rarities) // 0: Worthless, 1: Common, 2: Rare, 3: Epic, 4: Legendary, 5: Mythic, 6: Divine
    unsigned int state : 2;   // Bitmask: 0-3 (4 states) // 0: New, 1: Worn, 2: Broken, 3: Cursed
} ItemProperties;

typedef struct {
    int min_damage;
    int max_damage;
    char damage_type_en[20]; // e.g., "Slashing", "Piercing", "Bludgeoning"
    char damage_type_fr[20];
    int durability; // percentage (0-100) // indicates the condition of the weapon
    float range; // indicates the effective range of the weapon in meters
    float attack_speed; // indicates the speed of attack in seconds per hit
} Weapon;

typedef struct {
    int defense; // indicates the amount of damage the armor can absorb
    char resistances_en[50]; // e.g., "Fire, Ice, Poison"
    char resistances_fr[50];
    int slot; // 0: Head, 1: Chest, 2: Legs, 3: Hands, 4: Offhand
    float movement_penalty; // indicates the penalty to movement speed when wearing the armor
} Armor;

typedef struct {
    char effect_en[50]; // e.g., "Restores 50 HP", "Increases strength by 5"
    char effect_fr[50];
    int duration; // indicates how long the effect of the consumable is active after use
    float use_time; // indicates the time required to activate or consume the item
    int charges; // indicates the number of times the consumable can be used before it is depleted
} Consumable;

typedef struct {
    char quest_id[50]; // unique identifier for the quest item
    char story_en[100];
    char story_fr[100];
} QuestItem;

typedef struct {
    char harvest_location_en[50];
    char harvest_location_fr[50];
} Material;

// Union to hold specific item data based on the type
// This allows us to have a single structure for all item types while keeping the specific data separate
typedef union {
    Weapon weapon;
    Armor armor;
    Consumable consumable;
    QuestItem quest;
    Material material;
} ItemSpecific;

// Main item structure
// This structure contains all the generic properties of an item, as well as a union for specific properties
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

/* DATABASE */

// ItemDatabase - Represents a collection of items
// This structure holds an array of pointers to Item structures, along with a count and capacity
typedef struct {
    Item** items; // Array of pointers to Item structures
    int count; // Current number of items in the database
    int capacity; // Maximum capacity of the items array
} ItemDatabase;

ItemDatabase* load_items(const char* filename, int language);
void save_items(ItemDatabase* db, const char* filename);
void free_item_database(ItemDatabase* db);
ItemDatabase* create_item_database(int capacity);
void add_item_to_database(ItemDatabase* db, Item* item);
void save_single_item(Item* item, const char* filename);


#endif