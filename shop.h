#ifndef SHOP_H
#define SHOP_H
#include "item.h"
#include "inventory.h"
#include "utils.h"

void display_shop(Inventory* inv, ItemDatabase* db, int language);
void sell_items(Inventory* inv, int language);

#endif