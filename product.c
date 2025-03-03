// product.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "product.h"
#include "cart.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Thêm sản phẩm vào danh sách
void addProduct(Product *products, int *count, const char *name, float price, int quantity, const char *description, const char *category) {
    products[*count].count = *count;
    strcpy(products[*count].name, name);
    products[*count].price = price;
    products[*count].quantity = quantity;
    strcpy(products[*count].description, description);
    strcpy(products[*count].category, category);
    (*count)++;
}

void addProductToDB() {
    Product product;
    FILE *file = fopen(PRODUCT_FILE, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    system("clear");

    printf("=====================================\n");
    printf("           ADD NEW PRODUCT           \n");
    printf("=====================================\n\n");

    clearInputBuffer();

    printf("Enter product name: ");
    scanf("%[^\n]s", product.name);

    printf("Enter product price: ");
    scanf("%f", &product.price);
    
    printf("Enter product quantity: ");
    scanf("%d", &product.quantity);

    clearInputBuffer();

    printf("Enter prodcut description: ");
    scanf("%[^\n]s", product.description);

    clearInputBuffer();

    printf("Enter product category: ");
    scanf("%[^\n]s", product.category);

    fprintf(file, "%s, %f, %d, %s, %s\n", product.name, product.price, product.quantity, product.description, product.category);
    fclose(file);


    printf("Successfully added product.\n");
}

// Tìm kiếm sản phẩm theo từ khóa
void searchProduct(Product *products, int count) {

    char keyword[100];
    printf("Enter the keyword or category: ");

    getchar();  // Đọc ký tự '\n' còn sót lại từ scanf trước đó

    fgets(keyword, sizeof(keyword), stdin);  // Dùng fgets để đọc chuỗi có khoảng trắng
    keyword[strcspn(keyword, "\n")] = 0;


    int found = 0;
    printf("ID   | Name                           | Price       | Stock | Category\n");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        if (strstr(products[i].name, keyword) != NULL || strstr(products[i].category, keyword) != NULL) {
            printf("%-2d | %-30s | $%-10.2f | %-5d | %-6s\n", products[i].count, products[i].name, products[i].price, products[i].quantity,  products[i].category);
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
    printf("ID  | Name                           | Price       | Stock | Category\n");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-2d  | %-30s | $%-10.2f | %-5d | %-6s\n", products[i].count, products[i].name, products[i].price, products[i].quantity,  products[i].category);
        printf("\n");
    }

    printf("Press Enter to continue.\n");
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
