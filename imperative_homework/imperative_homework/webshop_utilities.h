#ifndef WEBSHOP_UTILITIES_H
#define WEBSHOP_UTILITIES_H

#include "product.h"

Product* findProduct(Product* array, int size, const char* name);
void resizeArray(Product** array, int* size, int newSize);
//void writeStoreToFile(const char* filename, Product* store, int storeSize);

#endif // WEBSHOP_UTILITIES_H

