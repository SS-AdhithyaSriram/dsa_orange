#include "cart.h"
#include <stdlib.h>
#include <stdio.h>

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
    printf("\033[1;34mCart Items:\033[0m\n");
    CartItem* item = cart_head;
    while (item) {
        Product* p = search_by_id(item->product_id);
        if (p) {
            printf("\033[1;32mID: %d, Name: %s, Quantity: %d, Price: %.2f\033[0m\n",
                   p->id, p->name, item->quantity, p->price);
        }
        item = item->next;
    }
    printf("\033[1;33mTotal: %.2f\033[0m\n", calculate_total());
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