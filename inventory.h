#ifndef INVENTORY_H
#define INVENTORY_H
#include "item.h"

typedef struct InventoryNode {
    Item* item;
    struct InventoryNode* next; // next - Conventional name used to create the linked list
} InventoryNode;

typedef struct {
    InventoryNode* head; // head - Conventional name to designate the first node of the linked list
    float total_weight;
    int phgold; // Amount of in-game currency (PHGold)
    float max_weight;
} Inventory;

Inventory* create_inventory(float max_weight);
void add_item(Inventory* inv, Item* item, int language);
void display_inventory(const Inventory* inv, int language);
void free_inventory(Inventory* inv);

#endif