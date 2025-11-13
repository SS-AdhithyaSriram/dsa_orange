#include "product.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

HashNode* hash_table[TABLE_SIZE];

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

int hash(int id) {
    return abs(id) % TABLE_SIZE;
}

void insert_product(Product* p) {
    int index = hash(p->id);
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    new_node->product = p;
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
}

Product* search_by_id(int id) {
    int index = hash(id);
    HashNode* node = hash_table[index];
    while (node) {
        if (node->product->id == id) {
            return node->product;
        }
        node = node->next;
    }
    return NULL;
}

Product* search_by_name(const char* name) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* node = hash_table[i];
        while (node) {
            if (strcmp(node->product->name, name) == 0) {
                return node->product;
            }
            node = node->next;
        }
    }
    return NULL;
}

void free_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* node = hash_table[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp->product);
            free(temp);
        }
    }
}