#include <stdio.h>
#include <string.h>
#include "user.h"

char loggedInUser[MAX_USERNAME] = "";

void registerUser() {
    User user;

    FILE *file = fopen(USER_FILE, "a");

    if(!file) {
	printf("Falied to open file\n");
	return;
    }

    printf("Enter Username: ");
    scanf("%s", user.username);

    printf("Enter Password: ");
    scanf("%s", user.password);

    fprintf(file, "%s %s\n", user.username, user.password);
    fclose(file);

    printf("User registed successfully.");
}

int loginUser() {
    User user;
    char username[MAX_USERNAME], password[MAX_PASSWORD];

    FILE *file = fopen(USER_FILE, "r");
    if(!file) {
	printf("No user data found. Please register first.\n");
	return 0;
    }

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    while(fscanf(file, "%s %s", user.username, user.password) != EOF) {
	if(strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
	    strcpy(loggedInUser, username);
	    printf("Successfully login! Welcome, %s.\n", username);
	    fclose(file);
	    return 1;
	} 
    }

    printf("Invalid username or password.\n");
    fclose(file);
    return 0;
}

void logoutUser() {
    if(strlen(loggedInUser) > 0) {
	printf("User %s logged out!\n", loggedInUser);
	strcpy(loggedInUser, "");
    } else {
	printf("User already logged out!.\n");
    }
}
