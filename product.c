// product.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "product.h"

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

void updateProduct(Product *product, int count) {
    FILE *file = fopen(PRODUCT_FILE, "r");
    FILE *temp = fopen(PRODUCT_TEMP_FILE, "w");

    if(!file) {
        printf("Error opening file!\n");
        return;
    }

    char line[512];

    int id = 0;

    printf("ID | Name                           | Price       | Stock | Category\n");
    printf("-------------------------------------------------------------------------\n");
    
    while (fgets(line, sizeof(line), file)) {
        char name[100], description[255], category[50];
        double price;
        int quantity;

        id++;

        sscanf(line, "%99[^,],%lf,%d,%255[^,],%49[^\n]", name, &price, &quantity, description, category);

        printf("%-2d | %-30s | $%-10.2lf | %-5d | %-6s\n", id, name, price, quantity, category);
    }

    int updateId;

    printf("\nPress \"-1\" to exit.");
    printf("\nEnter product number you want to update: ");
    scanf("%d", &updateId);

    if (updateId > id || updateId < -1) {
        printf("%d is too large or too small!!", updateId);
        return;
    }

    if(updateId == -1) {
        printf("\nPress any key to return...");

        return;
    }
    id = 0;
    char productName[100];
    int choice;

    rewind(file);

    while (fgets(line, sizeof(line), file)) 
    {
        char name[100], description[255], category[50];
        float price;
        int quantity;

        sscanf(line, "%99[^,],%f,%d,%255[^,],%49[^\n]", name, &price, &quantity, description, category);

        id++;

        if (id != updateId) { 
            fprintf(temp, "%s,%.2f,%d,%s,%s\n", name, price, quantity, description, category);
        }

        if(id == updateId) {
            printf("Current detail: \n");

            printf("ID | Name                           | Price       | Stock | Category\n");
            printf("-------------------------------------------------------------------------\n");
            printf("%-2d | %-30s | $%-10.2lf | %-5d | %-6s\n", id, name, price, quantity, category);

            printf("\nWhat do you want to update?\n");
            printf("1. Name\n");
            printf("2. Price\n");
            printf("3. Category\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            clearInputBuffer();

            if (choice == 1) {
                printf("Enter new name: ");
                scanf("%[^\n]s", name);
            } else if (choice == 2) {
                printf("Enter new price: ");
                scanf("%f", &price);
            } else if (choice == 3) {
                printf("Enter new category: ");
                scanf("%s", category);
            } else {
                printf("Invalid choice!\n");
                return;
            }

            fprintf(temp, "%s,%.2f,%d,%s,%s\n", name, price, quantity, description, category);

            break;
        }
        else {
            strcpy(productName, name);
        }
    }

    fclose(file);
    fclose(temp);

    remove(PRODUCT_FILE);
    rename(PRODUCT_TEMP_FILE, PRODUCT_FILE);

    printf("Updated \"%s\" from DB (txt file)\n", productName);
    printf("\nPress any key to return...");
}

void deleteProduct(Product *product, int count) {
    FILE *file = fopen(PRODUCT_FILE, "r");
    FILE *temp = fopen(PRODUCT_TEMP_FILE, "w");

    if (!file) {
        printf("error opening file!\n");
        return;
    }

    char line[512];

    int id = 0;

    printf("ID | Name                           | Price       | Stock | Category\n");
    printf("-------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        char name[100], description[255], category[50];
        float price;
        int quantity;

        id++;

        sscanf(line, "%99[^,],%f,%d,%255[^,],%49[^\n]", name, &price, &quantity, description, category);

        printf("%-2d | %-30s | $%-10.2f | %-5d | %-6s\n", id, name, price, quantity, category);
    }

    if (id == 0) {
        printf("There is no products left (we gone bankrupted)");

        fclose(file);
        fclose(temp);

        return;
    }

    int removeId;

    printf("\nPress \"-1\" to exit.");
    printf("\nEnter product number you want to remove: ");
    scanf("%d", &removeId);

    if (removeId > id || removeId < -1) {
        printf("%d is too large or too small!!", removeId);
        return;
    }

    if(removeId == -1) {
        printf("\nPress any key to return...");

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

    remove(PRODUCT_FILE);
    rename(PRODUCT_TEMP_FILE, PRODUCT_FILE);

    printf("Removed \"%s\" from DB (txt file)\n", productName);
    printf("\nPress any key to return...");
}

void addProductToDB() {
    Product product;
    FILE *file = fopen(PRODUCT_FILE, "a");
    if (!file) {
        printf("error opening file!\n");
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

    getchar();

    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;


    int found = 0;
    printf("ID  | Name                           | Price       | Stock | Category\n");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        if (strstr(products[i].name, keyword) != NULL || strstr(products[i].category, keyword) != NULL) {
            printf("%-2d  | %-30s | $%-10.2f | %-5d | %-6s\n", products[i].count, products[i].name, products[i].price, products[i].quantity,  products[i].category);
            found = 1;
        }
    }
    if (!found) {
        printf("No products found matching the keyword: %s\n", keyword); 
    }
    
    printf("\n\nPress any key to return...\n");
}

// In tất cả sản phẩm
void displayProducts(Product *products, int count) {
    if (count == 0) {
        printf("The product list is empty.\n"); 
        return;
    }
    printf("ID  | Name                           | Price       | Stock | Category\n");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 1; i < count; i++) {
        printf("%-2d  | %-30s | $%-10.2f | %-5d | %-6s\n", products[i].count, products[i].name, products[i].price, products[i].quantity,  products[i].category);
    }

    printf("\nPress Enter to continue...\n");
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
