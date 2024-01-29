#define _CRT_SECURE_NO_WARNINGS
#include "webshop_operations.h"
#include "webshop_utilities.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void loadStoreFromFile(const char* filename, Product** store, int* storeSize) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char name[50];
    int price, quantity;

    *storeSize = 0;

    while (fscanf(file, "%49s %d %d", name, &price, &quantity) == 3) {

        *store = realloc(*store, (*storeSize + 1) * sizeof(Product));
        if (!*store) {
            perror("Error reallocating memory");
            fclose(file);
            return;
        }
        strcpy((*store)[*storeSize].name, name);
        (*store)[*storeSize].price = price;
        (*store)[*storeSize].quantity = quantity;
        (*storeSize)++;
    }

    fclose(file);

    printf("Loaded products from '%s':\n", filename);
    for (int i = 0; i < *storeSize; i++) {
        printf("%s %d %d\n", (*store)[i].name, (*store)[i].price, (*store)[i].quantity);
    }
}

void writeStoreToFile(const char* filename, Product* store, int storeSize) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < storeSize; i++) {
        fprintf(file, "%s %d %d\n", store[i].name, store[i].price, store[i].quantity);
    }

    fclose(file);
}

void insertItemToCart(Product** cart, int* cartSize, const Product* store, int storeSize, Product item) {
    Product* productInStore = findProduct(store, storeSize, item.name);
    if (productInStore == NULL) {
        printf("Product '%s' not found in the store.\n", item.name);
        return;
    }

    item.price = productInStore->price;

    *cart = realloc(*cart, (*cartSize + 1) * sizeof(Product));
    if (*cart == NULL) {
        perror("Error reallocating memory");
        return;
    }

    (*cart)[*cartSize] = item;
    (*cartSize)++;
    printf("Inserting product: Name: %s, Price: %d, Quantity: %d\n", item.name, item.price, item.quantity);
}

void printCartContents(const Product* cart, int cartSize) {
    if (cartSize == 0) {
        printf("The cart is empty.\n");
        return;
    }

    printf("Cart Contents:\n");
    for (int i = 0; i < cartSize; i++) {
        printf("Product %d: Name: %s, Price: %d, Quantity: %d\n",
            i + 1, cart[i].name, cart[i].price, cart[i].quantity);
    }
}

int calculateCartPrice(Product* cart, int cartSize) {
    int total = 0;
    for (int i = 0; i < cartSize; i++) {
        total += cart[i].price * cart[i].quantity;
    }
    return total; 
}

void buyProducts(Product** store, int* storeSize, Product* cart, int* cartSize) {
    for (int i = 0; i < *cartSize; i++) {
        bool productFound = false;
        for (int j = 0; j < *storeSize; j++) {
            if (strcmp(cart[i].name, (*store)[j].name) == 0) {
                productFound = true;
                if ((*store)[j].quantity >= cart[i].quantity) {
                    (*store)[j].quantity -= cart[i].quantity;
                }
                else {
                    printf("%s: Only %d available, but %d requested.\n", cart[i].name, (*store)[j].quantity, cart[i].quantity);
                    (*store)[j].quantity = 0; 
                }
                break;
            }
        }
        if (!productFound) {
            printf("Product %s not found in store.\n", cart[i].name);
        }
    }
    printf("Products remaining in the shop:\n");
    for (int i = 0; i < *storeSize; i++) {
        printf("%s %d %d\n", (*store)[i].name, (*store)[i].price, (*store)[i].quantity);
    }
}

//void writeStoreToFile(const char* filename, Product* store, int storeSize) {
//    FILE* file = fopen(filename, "w");
//    if (!file) {
//        perror("Error opening file");
//        return;
//    }
//
//    for (int i = 0; i < storeSize; i++) {
//        fprintf(file, "%s %d %d\n", store[i].name, store[i].price, store[i].quantity);
//    }
//
//    fclose(file);
//}

