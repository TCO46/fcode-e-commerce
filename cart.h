#ifndef CART_H
#define CART_H

#include "product.h"

#define CART_FOLDER "cart/" // Thư mục chứa giỏ hàng

void addToCart(const char *username, Product product, int quantity);
void removeFromCart(const char *username);
void displayCart(const char *username);
void searchAndDisplayProducts(Product *products, int count, const char *username);

#endif
