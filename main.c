#include "product.h"
#include "cart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    init_hash_table();

    // product list
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

    int choice;
    while (1) {
        printf("\n________Shopping_Cart_Menu_______|\n");
        printf("1. Add to Cart                   |\n");
        printf("2. Remove from Cart              |\n");
        printf("3. Update Quantity               |\n");
        printf("4. Sort by Price (Low to High)   |\n");
        printf("5. Sort by Name (A-Z)            |\n");
        printf("6. Sort by Quantity (High to Low)|\n");
        printf("7. Display Cart                  |\n");
        printf("8. Exit                          |\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int id, qty;
                printf("Enter Product ID: ");
                scanf("%d", &id);
                printf("Enter Quantity: ");
                scanf("%d", &qty);
                add_to_cart(id, qty);
                display_cart();
                break;
            }
            case 2: {
                int id, qty;
                printf("Enter Product ID: ");
                scanf("%d", &id);
                printf("Enter Quantity to Remove: ");
                scanf("%d", &qty);
                remove_from_cart(id, qty);
                display_cart();
                break;
            }
            case 3: {
                int id, qty;
                printf("Enter Product ID: ");
                scanf("%d", &id);
                printf("Enter New Quantity: ");
                scanf("%d", &qty);
                update_cart_quantity(id, qty);
                display_cart();
                break;
            }
            case 4: {
                sort_cart_by_price();
                printf("Cart sorted by price.\n");
                display_cart();
                break;
            }
            case 5: {
                sort_cart_by_name();
                printf("Cart sorted by name.\n");
                display_cart();
                break;
            }
            case 6: {
                sort_cart_by_quantity();
                printf("Cart sorted by quantity.\n");
                display_cart();
                break;
            }
            case 7: {
                display_cart();
                break;
            }
            case 8: {
                printf("Exiting...\n");
                goto cleanup;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    }

cleanup:
    // Cleanup
    cleanup();

    return 0;
}