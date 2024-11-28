#include <stdio.h>
#include <string.h>
#include "SQL.h"

// Predefined admin credentials
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

void adminMenu() {
    int choice;
    while (1) {
        system("clear");
        printf("\nAdmin Menu");
        printf("\n==========\n");
        printf("1. Add student\n2. Remove student\n3. Add professor\n4. Remove professor\n5. Retrieve all students\n6. Retrieve all professors\n7. Post Notice\n8. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                remove_student();
                break;
            case 3:
                add_prof();
                break;
            case 4:
                remove_prof();
                break;
            case 5:
                retrieve_students();
                break;
            case 6:
                retrieve_profs();
                break;
            case 7:
                post_notice();
                break;
            case 8:
                return;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }
}

void adminPortal() {
    char username[30], password[30];
    system("clear");

    printf("\nAdmin Login\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("\nWelcome, Admin!\n");
        adminMenu();
    } else {
        printf("\nInvalid login details. Returning to main menu...\n");
    }
}