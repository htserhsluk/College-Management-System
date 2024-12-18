#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SQL.h"
#include "notice_board.h"

// Dummy faculty login credentials
// #define FACULTY_USERNAME "faculty1"
// #define FACULTY_PASSWORD "faculty123"

void facultyMenu(char prof_course[50]) {
    int choice;
    while (1) {
        printf("\nFaculty Menu");
        printf("\n============\n");
        printf("1. View students who have atleast x out of 100 marks\n2. Post Notice\n3. View notice board\n4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value of x: ");
                float x;
                scanf("%f", &x);
                marks(x, prof_course);
                break;
            case 2:
                create_notice();
                break;
            case 3:
                view_notice();
                break;
            case 4:
                return;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }
}

void facultyLogin() {
    char username[30], password[30], professor_data[100][4][50];

    // system("clear");
    printf("\nFaculty Login\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    profs_usernames(username, professor_data);
    if (strcmp(username, professor_data[0][0]) == 0 && strcmp(password, professor_data[0][1]) == 0) {
        printf("\nWelcome, Professor %s\n", professor_data[0][2]);
        char prof_course[50];
        strcpy(prof_course, professor_data[0][3]);
        facultyMenu(prof_course);
        return;
    }
    else printf("\nInvalid login details.\n");
}

void facultyPortal() {
    int choice;
    while (1) {
        // system("clear");
        printf("\nFaculty Portal");
        printf("\n==============\n");
        printf("1. Login\n2. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            facultyLogin();
        } else if (choice == 2) {
            return;
        } else {
            printf("\nInvalid choice. Try again.\n");
        }
    }
}