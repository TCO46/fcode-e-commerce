#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "user.h"

int main() {
	
	int choice;

	while(1) {
		system("clear");
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
					printf("Printing products");
				} else {
					printf("You need to login first");
				}
				break;
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
