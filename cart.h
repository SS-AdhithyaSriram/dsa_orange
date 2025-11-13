#ifndef CART_H
#define CART_H

#include "product.h"

// Function declarations
void add_to_cart(int product_id, int quantity);
void remove_from_cart(int product_id, int quantity);
float calculate_total();
void display_cart();
void cleanup();

#endif