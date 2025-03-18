#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cart.h"
#include "product.h"

// Thêm sản phẩm vào giỏ hàng
void addToCart(const char *username, Product product, int quantity) {
    char filename[100];
    sprintf(filename, "%s%s.txt", CART_FOLDER, username); // Tạo file theo username

    FILE *file = fopen(filename, "a"); 
    if (file == NULL) {
        printf("Error: Cannot open cart file for user %s\n", username);
        return;
    }

    fprintf(file, "%s,%.2f,%d,%s,%s\n", 
            product.name, product.price, quantity, 
            product.description, product.category);
    
    fclose(file);
    printf("Added %s (x%d) to cart for user %s\n", product.name, quantity, username);
}

void searchAndDisplayProducts(Product *products, int count, const char *username) {

    printf("\nAdd product to %s'cart:\n", username);
    printf("\nEnter keyword or category: ");

    getchar();

    char keyword[100];
    fgets(keyword, sizeof(keyword), stdin); 
    keyword[strcspn(keyword, "\n")] = 0; 


    int found = 0;

    Product matchedProducts[100];
    printf("\nProducts matching \"%s\":\n", keyword);

    for (int i = 0; i < count; i++) 
    {
        if (strstr(products[i].name, keyword) || strstr(products[i].category, keyword)) 
        {
            printf("%d. %s - $%.2f [%d available]\n", found + 1, products[i].name, products[i].price, products[i].quantity);
            matchedProducts[found] = products[i]; // Lưu sp thỏa mãn vào danh sách mới

            found++;
        }
    }

    if (found == 0) {
        printf("No matching products found.\n");
    }
    else 
    {
        int choice, quantity;


        printf("\nEnter product number you want to add: ");
        scanf("%d", &choice);

        printf("\nEnter the quantity to add: ");
        scanf("%d", &quantity);


        addToCart(username, matchedProducts[choice - 1], quantity);

    }

    printf("\nPress any key to return...");
}



// Xóa sản phẩm khỏi giỏ hàng
void removeFromCart(const char *username) 
{
    char filename[100], tempFile[100];
    sprintf(filename, "%s%s.txt", CART_FOLDER, username);
    sprintf(tempFile, "%s%s_temp.txt", CART_FOLDER, username);

    FILE *file = fopen(filename, "r");
    FILE *temp = fopen(tempFile, "w");

    if (file == NULL || temp == NULL) {
        printf("Error: Cannot open cart file for user %s\n", username);
        return;
    }

    printf("\n%s'cart:\n\n", username);

    char line[512];

    int id = 0;
    while (fgets(line, sizeof(line), file)) 
    {
        char name[100], description[255], category[50];
        float price;
        int quantity;

        id++;  

        sscanf(line, "%99[^,],%f,%d,%255[^,],%49[^\n]", name, &price, &quantity, description, category);
        printf("(%d):  \nName: %s\nPrice: %.2f\nQuantity: %d\nDescription: %s\nCategory: %s\n\n", id, name, price, quantity, description, category);
    }


    if (id == 0) {
        printf("Cart for %s is empty.\n", username);

        fclose(file);
        fclose(temp);

        remove(filename);  


        return;
    }

    int removeId;

    printf("\nEnter product number you want to remove: ");
    scanf("%d", &removeId);

    if (removeId > id || removeId < 1) {
        printf("%d is too large or too small!!", removeId);
        return;
    }


    id = 0;
    char productName[100];

    rewind(file);

    while (fgets(line, sizeof(line), file)) 
    {
        char name[100], description[255], category[50];
        float price;
        int quantity;

        sscanf(line, "%99[^,],%f,%d,%255[^,],%49[^\n]", name, &price, &quantity, description, category);

        id++;

        if (id != removeId) { 
            fprintf(temp, "%s,%.2f,%d,%s,%s\n", name, price, quantity, description, category);
        }
        else {
            strcpy(productName, name);
        }
    }


    fclose(file);
    fclose(temp);

    remove(filename);            // Xóa file cũ
    rename(tempFile, filename);  // Đổi tên file mới thành file gốc

    printf("Removed %s from cart\n", productName);
    printf("\nPress any key to return...");
}

void checkoutCart(char *username) {
    char checkOutName[100];
    sprintf(checkOutName, "%s%s.txt", CHECKOUT_FOLDER, username);

    FILE *fileCheckOut = fopen(checkOutName, "a");
    if(fileCheckOut == NULL) {
        printf("Error opening file 2!\n");
        return;
    }

    char cartName[100];
    sprintf(cartName, "%s%s.txt", CART_FOLDER, username);

    FILE *fileCart = fopen(cartName, "r");
    if(fileCart == NULL) {
        printf("Error opening file 1!\n");
        return;
    }

    char name[100], description[255], category[50];
    float price, total = 0;
    int quantity;

    while (fscanf(fileCart, "%99[^,],%f,%d,%255[^,],%49[^\n]\n", name, &price, &quantity, description, category) == 5) {
        fprintf(fileCheckOut, "%s, %d, %.2f, %s\n", name, quantity, price, category);
    }


    fclose(fileCheckOut);
    fclose(fileCart);

    remove(cartName);
    
    printf("Successfully checkouted.");
}

// Hiển thị giỏ hàng
void displayCart(const char *username) {
    char filename[100];
    sprintf(filename, "%s%s.txt", CART_FOLDER, username);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nCart for %s is empty or does not exist.\n", username);
        return;
    }

    char name[100], description[255], category[50];
    float price, total = 0;
    int quantity;

    printf("\nCart for %s:\n", username);
    while (fscanf(file, "%99[^,],%f,%d,%255[^,],%49[^\n]\n", name, &price, &quantity, description, category) == 5) {
        printf("  - %s (x%d) - %.2f$\n", name, quantity, price * quantity);
        total += price * quantity;
    }

    printf("\nTotal: %.2f$\n", total);

    char options;

    printf("\nDo you want to checkout now? [y/n] ");

    clearInputBuffer();
    scanf("%s", &options);

    if(options == 'n') {
        printf("\nPress any key to return...");
        return;
    } else {
        checkoutCart((char*)username);
    }


    fclose(file);
}

