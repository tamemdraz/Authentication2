#include <stdio.h>
#include <string.h>

#define MAX_USERS 30
#define MAX_STRING_SIZE 100

struct User {
    char user[MAX_STRING_SIZE];
    char pass[MAX_STRING_SIZE];
    union {
        int active;
        _Bool isActive;
    };
};

struct User users[MAX_USERS];
int count = 0;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void registerUser() {
    if (count >= MAX_USERS) {
        printf("Can't register more users.\n");
        return;
    }

    printf("Enter a user: ");
    scanf("%99s", users[count].user);

    printf("\nEnter a pass: ");
    scanf("%99s", users[count].pass);

    char activeInput[10];
    printf("\nChoose user status (\"false\" or 0 for inactive, \"true\" or 1 for active): ");
    scanf("%9s", activeInput);

    if (strcmp(activeInput, "true") == 0) {
        users[count].active = 1;
    } else {
        users[count].active = 0;
    }

    count++;

    printf("Registered successfully.\n");
}



int authenticateUser() {
    char username[MAX_STRING_SIZE];
    char password[MAX_STRING_SIZE];

    printf("Enter username: ");
    scanf("%99s", username); 

    printf("\nEnter password: ");
    scanf("%99s", password); 

    for (int i = 0; i < count; i++) {
        if (strcmp(username, users[i].user) == 0 && strcmp(password, users[i].pass) == 0) {
            if (users[i].active) {
                return 1;
            } else {
                printf("You are not an active user.\n");
                return 0;
            }
        }
    }

    printf("Login failed. Please try again.\n");
    return 0;
}


enum MenuChoice { REGISTER = 1, LOGIN, EXIT };

int main() {
    int choice;
    int authenticated = 0;

    while (1) {
        printf("1. Register\n2. Login\n3. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case REGISTER:
                registerUser();
                break;
            case LOGIN:
                authenticated = authenticateUser();
                if (authenticated) {
                    printf("Welcome, %s!\n", users[count - 1].user);
                }
                break;
            case EXIT:
                printf("End!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
