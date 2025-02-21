#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "user.h"

#include "product.h"

int main() {
	
	int choice;

	Product products[MAX_PRODUCTS];

    // Đọc sản phẩm từ file PRODUCT_FILE (đã được định nghĩa trong product.h)
    int productCount = readProductsFromFile(products);


	while(1) {
		// system("clear");
		system("cls");
		showTitle();
		showMenu();
		scanf("%d", &choice);


		switch (choice) {
			case 1:
				registerUser();
				break;
			case 2:
				if (loginUser()) {
				    printf("User %s is now logged in.\n", loggedInUser);
				}
				break;
			case 3:
				logoutUser();
				break;
			case 4:
				if(strlen(loggedInUser) > 0) {

				    if (productCount == 0) {
				        printf("No products avalible.\n");
				    } else {
					    // Hiển thị tất cả sản phẩm
					    printf("List of Products:\n \n");
					    displayProducts(products, productCount);
					}
					

				} else {
					printf("You need to login first");
				}

				break;
			case 5:{

				if(strlen(loggedInUser) > 0) {

					char keyword[100];
	                printf("Enter the keyword or category: ");

	                getchar();  // Đọc ký tự '\n' còn sót lại từ scanf trước đó

	                fgets(keyword, sizeof(keyword), stdin);  // Dùng fgets để đọc chuỗi có khoảng trắng
	                keyword[strcspn(keyword, "\n")] = 0;  // Loại bỏ dấu '\n' nếu có

	                searchProduct(products, productCount, keyword);
	            }
	            else {
					printf("You need to login first");
				}


				break;
			}
			case -1:
				printf("Exiting...");
				return 0;
			default:
				printf("Invalid choice. Please try again!");
		}
		getchar();
		getchar();
	}
	

	return 0;
}
