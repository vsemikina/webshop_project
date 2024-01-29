#ifndef WEBSHOP_OPERATIONS_H
#define WEBSHOP_OPERATIONS_H

#include "product.h" 

void loadStoreFromFile(const char* filename, Product** store, int* storeSize);
void writeStoreToFile(const char* filename, Product* store, int storeSize);
void insertItemToCart(Product** cart, int* cartSize, const Product* store, int storeSize, Product item);
void printCartContents(const Product* cart, int cartSize);
int calculateCartPrice(Product* cart, int cartSize);
void buyProducts(Product** store, int* storeSize, Product* cart, int* cartSize);
void writeStoreToFile(const char* filename, Product* store, int storeSize);

#endif // WEBSHOP_OPERATIONS_H
