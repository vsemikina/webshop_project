#define _CRT_SECURE_NO_WARNINGS

#include "webshop_utilities.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Product* findProduct(Product* array, int size, const char* name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(array[i].name, name) == 0) {
            return &array[i]; 
        }
    }
    return NULL;
}

void resizeArray(Product** array, int* size, int newSize) {
    if (newSize <= 0) {
        printf("Invalid new size.\n");
        return;
    }

    Product* temp = realloc(*array, newSize * sizeof(Product));
    if (temp == NULL) {
        perror("Error reallocating memory");
        return;
    }

    *array = temp;
    *size = newSize; 

    printf("Array resized. New size: %d\n", *size);
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