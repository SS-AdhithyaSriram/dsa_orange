#include "cart.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

CartItem* cart_head = NULL;

void add_to_cart(int product_id, int quantity) {
    Product* p = search_by_id(product_id);
    if (!p || p->stock < quantity) {
        printf("Product not found or insufficient stock.\n");
        return;
    }
    CartItem* item = cart_head;
    while (item) {
        if (item->product_id == product_id) {
            item->quantity += quantity;
            p->stock -= quantity;
            return;
        }
        item = item->next;
    }
    // New item
    CartItem* new_item = (CartItem*)malloc(sizeof(CartItem));
    new_item->product_id = product_id;
    new_item->quantity = quantity;
    new_item->next = NULL;
    if (!cart_head) {
        cart_head = new_item;
    } else {
        CartItem* temp = cart_head;
        while (temp->next) temp = temp->next;
        temp->next = new_item;
    }
    p->stock -= quantity;
}

void remove_from_cart(int product_id, int quantity) {
    CartItem* item = cart_head;
    CartItem* prev = NULL;
    while (item) {
        if (item->product_id == product_id) {
            if (item->quantity > quantity) {
                item->quantity -= quantity;
            } else {
                quantity = item->quantity;
                if (prev) {
                    prev->next = item->next;
                } else {
                    cart_head = item->next;
                }
                free(item);
            }
            Product* p = search_by_id(product_id);
            if (p) p->stock += quantity;
            return;
        }
        prev = item;
        item = item->next;
    }
    printf("Product not in cart.\n");
}

void update_cart_quantity(int product_id, int new_quantity) {
    if (new_quantity <= 0) {
        remove_from_cart(product_id, 9999); // Remove all
        return;
    }
    CartItem* item = cart_head;
    while (item) {
        if (item->product_id == product_id) {
            int diff = new_quantity - item->quantity;
            Product* p = search_by_id(product_id);
            if (p && p->stock >= diff) {
                item->quantity = new_quantity;
                p->stock -= diff;
            } else {
                printf("Insufficient stock for update.\n");
            }
            return;
        }
        item = item->next;
    }
    printf("Product not in cart.\n");
}

// Helper function to get cart size
int get_cart_size() {
    int count = 0;
    CartItem* item = cart_head;
    while (item) {
        count++;
        item = item->next;
    }
    return count;
}

// Helper function to get cart as array
CartItem** get_cart_array(int* size) {
    *size = get_cart_size();
    CartItem** arr = (CartItem**)malloc(*size * sizeof(CartItem*));
    CartItem* item = cart_head;
    for (int i = 0; i < *size; i++) {
        arr[i] = item;
        item = item->next;
    }
    return arr;
}

// Helper function to rebuild cart from array
void rebuild_cart(CartItem** arr, int size) {
    cart_head = NULL;
    for (int i = 0; i < size; i++) {
        arr[i]->next = (i < size - 1) ? arr[i+1] : NULL;
    }
    if (size > 0) cart_head = arr[0];
    free(arr);
}

void sort_cart_by_price() {
    int size;
    CartItem** arr = get_cart_array(&size);
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            Product* p1 = search_by_id(arr[j]->product_id);
            Product* p2 = search_by_id(arr[j+1]->product_id);
            if (p1 && p2 && p1->price > p2->price) {
                CartItem* temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    rebuild_cart(arr, size);
}

void sort_cart_by_name() {
    int size;
    CartItem** arr = get_cart_array(&size);
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            Product* p1 = search_by_id(arr[j]->product_id);
            Product* p2 = search_by_id(arr[j+1]->product_id);
            if (p1 && p2 && strcmp(p1->name, p2->name) > 0) {
                CartItem* temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    rebuild_cart(arr, size);
}

void sort_cart_by_quantity() {
    int size;
    CartItem** arr = get_cart_array(&size);
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j]->quantity < arr[j+1]->quantity) {
                CartItem* temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    rebuild_cart(arr, size);
}

float calculate_total() {
    float total = 0.0;
    CartItem* item = cart_head;
    while (item) {
        Product* p = search_by_id(item->product_id);
        if (p) {
            total += p->price * item->quantity;
        }
        item = item->next;
    }
    if (total > 100.0) {
        total *= 0.85; // 15% discount
    }
    return total;
}

void display_cart() {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                SHOPPING CART                                 ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════╣\n");

    CartItem* item = cart_head;
    int item_count = 0;
    float subtotal = 0.0;

    if (!item) {
        printf("║                                 Cart is empty!                               ║\n");
        printf("║                                                                              ║\n");
        printf("║                                                                              ║\n");
        printf("║                                                                              ║\n");
        printf("║                                                                              ║\n");
    } else {
        while (item) {
            Product* p = search_by_id(item->product_id);
            if (p) {
                float item_total = p->price * item->quantity;
                subtotal += item_total;
                printf("║  %-10s (ID: %2d)  Qty: %2d  Price: $%5.2f  Total: $%7.2f                ║\n",
                       p->name, p->id, item->quantity, p->price, item_total);
                item_count++;
            }
            item = item->next;
        }

        // Fill empty lines if less than 5 items
        for (int i = item_count; i < 5; i++) {
            printf("║                                                                              ║\n");
        }
    }

    printf("╠══════════════════════════════════════════════════════════════════════════════╣\n");

    float discount = 0.0;
    float total = calculate_total();
    if (subtotal > 100.0) {
        discount = subtotal * 0.15;
    }

    printf("║  Subtotal: $%7.2f                    Discount: $%7.2f                    ║\n", subtotal, discount);
    printf("║  Grand Total: $%7.2f                                                       ║\n", total);
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
}

void cleanup() {
    CartItem* item = cart_head;
    while (item) {
        CartItem* temp = item;
        item = item->next;
        free(temp);
    }
    free_hash_table();
}