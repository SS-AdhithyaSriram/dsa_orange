#include "product.h"
#include "cart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    init_hash_table();

    // Create some products
    Product* p1 = (Product*)malloc(sizeof(Product));
    p1->id = 1;
    strcpy(p1->name, "Apple");
    p1->price = 2.5;
    p1->stock = 10;
    insert_product(p1);

    Product* p2 = (Product*)malloc(sizeof(Product));
    p2->id = 2;
    strcpy(p2->name, "Banana");
    p2->price = 1.0;
    p2->stock = 20;
    insert_product(p2);

    Product* p3 = (Product*)malloc(sizeof(Product));
    p3->id = 3;
    strcpy(p3->name, "Orange");
    p3->price = 3.0;
    p3->stock = 50;
    insert_product(p3);

    // Test search
    Product* found = search_by_id(1);
    if (found) printf("Found by ID: %s\n", found->name);

    found = search_by_name("Banana");
    if (found) printf("Found by name: %d\n", found->id);

    // Test add to cart
    add_to_cart(1, 2);
    add_to_cart(2, 3);
    add_to_cart(3, 40); // Add more for discount
    add_to_cart(1, 1); // Add more to existing

    // Display cart
    display_cart();

    // Remove from cart
    remove_from_cart(1, 1);

    // Display again
    display_cart();

    // Cleanup
    cleanup();

    return 0;
}