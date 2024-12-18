#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "faculty.h"
#include "admin.h"
#include "SQL.h"
#include "notice_board.h"

// ANSI color codes
#define RESET "\033[0m"       // Reset to default
#define RED "\033[31m"        // Red color
#define GREEN "\033[32m"      // Green color
#define YELLOW "\033[33m"     // Yellow color
#define BLUE "\033[34m"       // Blue color
#define MAGENTA "\033[35m"    // Magenta color
#define CYAN "\033[36m"       // Cyan color

void displayAsciiArt() {
    // Print ASCII art using jp2a
    if (system("jp2a --width=50 iiitb_logo.jpg") != 0) { // Adjust width for smaller display
        printf(RED "Error: Failed to display ASCII art. Make sure 'jp2a' is installed and the image file exists.\n" RESET);
    }
}

void mainMenu() {
    int choice;
    while (1) {
        system("clear");  // Use "clear" for Linux/Mac instead of "cls"

        displayAsciiArt(); //Display the logo ASCII Art

        printf(BLUE "\n========================================" RESET);
        printf(CYAN "\n   Welcome to IIIT Bangalore System" RESET);
        printf(BLUE "\n========================================" RESET);
        printf(YELLOW "\n1. Student" RESET);
        printf(GREEN "\n2. Faculty" RESET);
        printf(MAGENTA "\n3. Admin" RESET);
        printf(RED "\n4. Exit" RESET);
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf(YELLOW "\nOpening Student Portal...\n" RESET);
                studentPortal();
                break;
            case 2:
                printf(GREEN "\nOpening Faculty Portal...\n" RESET);
                facultyPortal();
                break;
            case 3:
                printf(MAGENTA "\nOpening Admin Portal...\n" RESET);
                adminPortal();
                break;
            case 4:
                printf(RED "\nExiting the system. Goodbye!\n" RESET);
                exit(0);
            default:
                printf(RED "\nInvalid choice. Please try again.\n" RESET);
        }
    }
}

int main() {
    mainMenu();
    return 0;
}