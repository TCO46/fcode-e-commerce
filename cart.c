#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cart.h"
#include "product.h"


// 🛒 Thêm sản phẩm vào giỏ hàng
void addToCart(const char *username, Product product, int quantity) {
    char filename[100];
    sprintf(filename, "%s%s.txt", CART_FOLDER, username); // Tạo file theo username

    FILE *file = fopen(filename, "a"); // Mở file ở chế độ append (thêm dữ liệu)
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




void searchAndDisplayProducts(Product *products, int count, const char *keyword, const char *username) {

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

        getchar();


        addToCart(username, matchedProducts[choice - 1], quantity);

    }
}



// ❌ Xóa sản phẩm khỏi giỏ hàng
void removeFromCart(const char *username, const char *productName) {
    char filename[100], tempFile[100];
    sprintf(filename, "%s%s.txt", CART_FOLDER, username);
    sprintf(tempFile, "%s%s_temp.txt", CART_FOLDER, username);

    FILE *file = fopen(filename, "r");
    FILE *temp = fopen(tempFile, "w");

    if (file == NULL || temp == NULL) {
        printf("Error: Cannot open cart file for user %s\n", username);
        return;
    }

    char line[512];
    int removed = 0;

    while (fgets(line, sizeof(line), file)) {
        char name[100], description[255], category[50];
        float price;
        int quantity;

        sscanf(line, "%99[^,],%f,%d,%255[^,],%49[^\n]", name, &price, &quantity, description, category);
        
        if (strcmp(name, productName) != 0) { 
            fprintf(temp, "%s,%.2f,%d,%s,%s\n", name, price, quantity, description, category);
        } else {
            removed = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(filename);            // Xóa file cũ
    rename(tempFile, filename);  // Đổi tên file mới thành file gốc

    if (removed) {
        printf("Removed %s from cart for user %s\n", productName, username);
    } else {
        printf("Product %s not found in cart\n", productName);
    }
}

// 🛒 Hiển thị giỏ hàng
void displayCart(const char *username) {
    char filename[100];
    sprintf(filename, "%s%s.txt", CART_FOLDER, username);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cart for %s is empty or does not exist.\n", username);
        return;
    }

    char name[100], description[255], category[50];
    float price, total = 0;
    int quantity;

    printf("Cart for %s:\n", username);
    while (fscanf(file, "%99[^,],%f,%d,%255[^,],%49[^\n]\n", name, &price, &quantity, description, category) == 5) {
        printf("  - %s (x%d) - %.2f$\n", name, quantity, price * quantity);
        total += price * quantity;
    }

    printf("Total: %.2f$\n", total);
    fclose(file);
}
