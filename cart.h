#ifndef CART_H
#define CART_H

#include "product.h"

typedef struct CartItem {
    int product_id;
    int quantity;
    struct CartItem* next;
} CartItem;

// Function declarations
void add_to_cart(int product_id, int quantity);
void remove_from_cart(int product_id, int quantity);
void update_cart_quantity(int product_id, int new_quantity);
void sort_cart_by_price();
void sort_cart_by_name();
void sort_cart_by_quantity();
float calculate_total();
void display_cart();
void cleanup();

#endif