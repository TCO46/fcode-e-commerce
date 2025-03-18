// product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_PRODUCTS 100
#define MAX_NAME_CHAR 100
#define MAX_DESCRIPTION_CHAR 255
#define MAX_CATEGORY_CHAR 50

#define PRODUCT_FILE "product.txt"
#define PRODUCT_TEMP_FILE "tempProduct.txt"

typedef struct {
    int count;
    char name[100];
    float price;
    int quantity;
    char description[256];
    char category[50];
} Product;

void addProduct(Product *products, int *count, const char *name, float price, int quantity, const char *description, const char *category);
void updateProduct(Product *product, int count);
void deleteProduct(Product *product, int count);
void searchProduct(Product *products, int count);
void displayProducts(Product *products, int count);
void addProductToDB();
void clearInputBuffer();

// Hàm đọc sản phẩm từ file
int readProductsFromFile(Product *products);

#endif // PRODUCT_H

