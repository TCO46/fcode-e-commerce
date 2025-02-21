// product.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "product.h"

// Thêm sản phẩm vào danh sách
void addProduct(Product *products, int *count, const char *name, float price, int quantity, const char *description, const char *category) {
    strcpy(products[*count].name, name);
    products[*count].price = price;
    products[*count].quantity = quantity;
    strcpy(products[*count].description, description);
    strcpy(products[*count].category, category);
    (*count)++;
}

// Tìm kiếm sản phẩm theo từ khóa
void searchProduct(Product *products, int count, const char *keyword) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(products[i].name, keyword) != NULL || strstr(products[i].category, keyword) != NULL) {
            printf("Product found: %s\n", products[i].name);  // "Sản phẩm tìm thấy"
            printf("  Price: %.2f\n", products[i].price);     // "Giá"
            printf("  Quantity: %d\n", products[i].quantity); // "Số lượng"
            printf("  Description: %s\n", products[i].description); // "Mô tả"
            printf("  Category: %s\n", products[i].category); // "Danh mục"
            printf("\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No products found matching the keyword: %s\n", keyword); 
    }
}

// In tất cả sản phẩm
void displayProducts(Product *products, int count) {
    if (count == 0) {
        printf("The product list is empty.\n"); 
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("Product: %s\n", products[i].name); 
        printf("  Price: %.2f\n", products[i].price);
        printf("  Quantity: %d\n", products[i].quantity); 
        printf("  Description: %s\n", products[i].description); 
        printf("  Category: %s\n", products[i].category); 
        printf("\n");
    }
}

// Đọc sản phẩm từ file PRODUCT_FILE
int readProductsFromFile(Product *products) {
    FILE *file = fopen(PRODUCT_FILE, "r");  
    if (file == NULL) {
        printf("Cannot open file %s\n", PRODUCT_FILE);  
        return 0;  // Thất bại nếu không thể mở file
    }

    char line[512];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        char name[100], description[255], category[50];
        float price;
        int quantity;

        // Dùng sscanf để tách dữ liệu từ mỗi dòng
        if (sscanf(line, "%99[^,],%f,%d,%255[^,],%49[^\n]", name, &price, &quantity, description, category) == 5) {
            addProduct(products, &count, name, price, quantity, description, category);
        }
    }

    fclose(file);
    return count;  // Trả về số lượng sản phẩm đã đọc
}
