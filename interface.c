#include <stdio.h>
#include "interface.h"

void showTitle() {
    printf("=====================================\n");
    printf("      WELCOME TO CLI E-COMMERCE      \n");
    printf("=====================================\n\n");
}

void showMenu() {
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Logout\n");
    printf("4. View Products\n");
    printf("5. Search Products\n");
    printf("6. Add new product\n");
    printf("7. Add product to cart\n");
    printf("8. Remove product to cart\n");
    printf("9. View cart\n");
    printf("e. Exit\n");
    printf("\nChoose an option: ");
}
