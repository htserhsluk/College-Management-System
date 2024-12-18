#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SQL.h"
#include "notice_board.h"

// Dummy student login credentials
// #define STUDENT_USERNAME "student1"
// #define STUDENT_PASSWORD "student123"

void studentMenu(char *name, char *username, char *courses, char *attendance) {
    int choice;
    while (1) {
        printf("\nStudent Menu");
        printf("\n============\n");
        printf("1. View your courses\n2. View your pending fees\n3. View notice board\n4. View your academic report\n5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_courses(username);
                break;
            case 2:
                view_fees(username);
                break;
            case 3:
                view_notice();
                break;
            case 4:
                view_acad_report(name, username, courses, attendance);
                break;
            case 5:
                return;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }
}

// Function to simulate student login
void studentLogin() {
    char username[30], password[30], student_data[100][5][150];
    int attempts = 3;

    while (attempts--) {
        // system("cls");
        printf("\nStudent Login");
        printf("\n=============\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);
        students_usernames(username, student_data);
        if (strcmp(username, student_data[0][0]) == 0 && strcmp(password, student_data[0][1]) == 0) {
            printf("\nLogin successful! Welcome, %s\n", student_data[0][2]);
            char *courses = student_data[0][3];
            char *name = student_data[0][2];
            char *attendance = student_data[0][4];
            studentMenu(name, username, courses, attendance);
            return;
        } else {
            printf("\nInvalid credentials. Remaining attempts: %d\n", attempts);
        }
    }
    printf("\nLogin failed. Returning to main menu...\n");
}

void studentPortal() {
    int choice;
    while (1) {
        // system("clear");
        printf("\nStudent Portal");
        printf("\n==============\n");
        printf("1. Login\n2. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                studentLogin();
                break;
            case 2:
                return;  // Exit to main menu
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }
}