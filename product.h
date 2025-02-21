// product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_PRODUCTS 100

#define PRODUCT_FILE "product.txt"  // Định nghĩa tên file sản phẩm

typedef struct {
    char name[100];
    float price;
    int quantity;
    char description[255];
    char category[50];
} Product;

void addProduct(Product *products, int *count, const char *name, float price, int quantity, const char *description, const char *category);
void searchProduct(Product *products, int count, const char *keyword);
void displayProducts(Product *products, int count);

// Hàm đọc sản phẩm từ file
int readProductsFromFile(Product *products);

#endif // PRODUCT_H
