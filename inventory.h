#ifndef INVENTORY_H
#define INVENTORY_H
#include "item.h"

// InventoryNode - Represents a node in the linked list of items in the inventory
typedef struct InventoryNode {
    Item* item;
    struct InventoryNode* next; // next - Conventional name used to create the linked list
} InventoryNode;

// Inventory - Represents the player's inventory
typedef struct {
    InventoryNode* head; // head - Conventional name to designate the first node of the linked list
    float total_weight; // Total weight of items in the inventory
    int phgold; // Amount of in-game currency (PHGold)
    float max_weight; // Maximum weight the inventory can hold
} Inventory;

Inventory* create_inventory(float max_weight);
void add_item(Inventory* inv, Item* item, int language);
void display_inventory(const Inventory* inv, int language);
void free_inventory(Inventory* inv);
void load_inventory(Inventory* inv, const char* filename, ItemDatabase* db, int language);
void save_inventory(Inventory* inv, const char* filename);

#endif