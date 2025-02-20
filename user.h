#ifndef USER_H
#define USER_H

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define USER_FILE "users.txt"

typedef struct {
	char username[MAX_USERNAME];
	char password[MAX_PASSWORD];
} User;

extern char loggedInUser[MAX_USERNAME];

void registerUser();
int loginUser();
void logoutUser();

#endif
