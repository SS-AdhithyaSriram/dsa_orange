#ifndef PRODUCT_H
#define PRODUCT_H

#define TABLE_SIZE 100

typedef struct Product {
    int id;
    char name[50];
    float price;
    int stock;
} Product;

typedef struct HashNode {
    Product* product;
    struct HashNode* next;
} HashNode;

typedef struct CartItem {
    int product_id;
    int quantity;
    struct CartItem* next;
} CartItem;

// Function declarations
int hash(int id);
void insert_product(Product* p);
Product* search_by_id(int id);
Product* search_by_name(const char* name);
void init_hash_table();
void free_hash_table();

#endif