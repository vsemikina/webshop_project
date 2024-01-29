#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "webshop_operations.h"
#include "webshop_utilities.h" 




int main() {
    Product* store = NULL;
    int storeSize = 0;
    Product* cart = NULL;
    int cartSize = 0;

    char filename[100];
    Product tempProduct;
    int choice, totalPrice;

    do {
        printf("\n ~~~ Webshop Menu ~~~\n");
        printf("1. Load webshop store from a file\n");
        printf("2. Write the content of the store to a file\n");
        printf("3. Insert an item to cart\n");
        printf("4. Get the price of cart\n");
        printf("5. Buy the products\n");
        printf("6. Exit\n");
        printf("Enter the number of your choice: ");
        scanf("%d", &choice);


        switch (choice) {
        case 1:
            printf("Enter filename to load: ");
            scanf("%s", filename);
            loadStoreFromFile(filename, &store, &storeSize);
            break;
        case 2:
            printf("Enter filename to write to: ");
            scanf("%s", filename);
            writeStoreToFile(filename, store, storeSize);
            break;


        case 3:
            //tempProduct.price = 0;
            printf("Enter product name: ");
            scanf("%s", tempProduct.name);

            printf("Enter quantity: ");
            scanf("%d", &tempProduct.quantity);
            insertItemToCart(&cart, &cartSize, store, storeSize, tempProduct);
            printCartContents(cart, cartSize);
            break;
        case 4:
            totalPrice = calculateCartPrice(cart, cartSize);
            printf("Total price of cart: %d\n", totalPrice);
            break;
        case 5:
            buyProducts(&store, &storeSize, cart, &cartSize);
            writeStoreToFile(filename, store, storeSize);
            break;
        case 6:
            printf("Exiting program.\n");
            free(store);
            free(cart);
            return 0;
        default:
            printf("Invalid choice, please try again.\n");

        }


    } while (choice != 6);

    free(store);
    free(cart);

    return 0;
}