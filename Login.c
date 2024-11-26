#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>  // For Windows systems; for Linux, replace `getch()` with termios implementation

// Constants
#define MAX_USERS 100
#define USERNAME_LEN 30
#define PASSWORD_LEN 20
#define ROLLNO_LEN 15
#define ROLE_LEN 10

// User structure
typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char rollNo[ROLLNO_LEN];
    char role[ROLE_LEN];
} User;

// Global Variables
User users[MAX_USERS];
int userCount = 0;

// Function Declarations
void displayMenu();
void login();
void signUp();
void forgotPassword();
void adminMenu();
void viewUsers();
void deleteUser();
void printHeader(const char *header);
void getPassword(char *password);
int isStrongPassword(const char *password);
void saveUsersToFile();
void loadUsersFromFile();

// Main Function
int main() {
    int choice;

    loadUsersFromFile(); // Load user data from file at the start

    while (1) {
        system("cls"); // Use system("clear") for Linux/Mac
        printHeader("Welcome to IIIT Bangalore Login System");
        displayMenu();

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                signUp();
                break;
            case 3:
                forgotPassword();
                break;
            case 4:
                printf("\nThank you for using the system. Goodbye!\n");
                saveUsersToFile(); // Save user data to file before exiting
                exit(0);
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
        printf("\nPress Enter to continue...");
        getchar();
        getchar();  // Pause the program
    }
    return 0;
}

// Function to display the main menu
void displayMenu() {
    printf("\n1. Login");
    printf("\n2. Sign-Up");
    printf("\n3. Forgot Password");
    printf("\n4. Exit\n");
}

// Function to print a formatted header
void printHeader(const char *header) {
    int len = strlen(header);
    int padding = (120 - len) / 2;
    printf("\n========================================================================================================================\n");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s\n", header);
    printf("========================================================================================================================\n");
}

// Secure password input with masking
void getPassword(char *password) {
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r') {  // Enter key terminates
        if (ch == '\b' && i > 0) {   // Handle backspace
            printf("\b \b");
            i--;
        } else {
            printf("*");
            password[i++] = ch;
        }
    }
    password[i] = '\0';
    printf("\n");
}

// Validate password strength
int isStrongPassword(const char *password) {
    int hasLower = 0, hasUpper = 0, hasDigit = 0, hasSpecial = 0;
    for (int i = 0; password[i]; i++) {
        if (password[i] >= 'a' && password[i] <= 'z') hasLower = 1;
        if (password[i] >= 'A' && password[i] <= 'Z') hasUpper = 1;
        if (password[i] >= '0' && password[i] <= '9') hasDigit = 1;
        if (strchr("!@#$%^&*()-_=+[]{};:'\",.<>?/\\|`~", password[i])) hasSpecial = 1;
    }
    return hasLower && hasUpper && hasDigit && hasSpecial;
}

// Function to handle user login
void login() {
    char username[USERNAME_LEN], rollNo[ROLLNO_LEN], password[PASSWORD_LEN];
    int found = 0;

    system("cls");
    printHeader("Login Page");

    printf("\nEnter Username: ");
    scanf("%s", username);
    printf("Enter Roll Number: ");
    scanf("%s", rollNo);
    printf("Enter Password: ");
    getPassword(password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].rollNo, rollNo) == 0 &&
            strcmp(users[i].password, password) == 0) {
            found = 1;
            printf("\nLogin Successful! Welcome, %s (%s)!\n", username, users[i].role);
            if (strcmp(users[i].role, "Admin") == 0) adminMenu();
            break;
        }
    }

    if (!found) printf("\nInvalid Username, Roll Number, or Password. Please try again.\n");
}

// Function to handle user sign-up
void signUp() {
    char username[USERNAME_LEN], password[PASSWORD_LEN], confirmPassword[PASSWORD_LEN], rollNo[ROLLNO_LEN], role[ROLE_LEN];

    system("cls");
    printHeader("Sign-Up Page");

    if (userCount >= MAX_USERS) {
        printf("\nUser limit reached! Cannot add more users.\n");
        return;
    }

    printf("\nCreate Username: ");
    scanf("%s", username);
    printf("Enter Roll Number (Unique): ");
    scanf("%s", rollNo);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].rollNo, rollNo) == 0) {
            printf("\nRoll Number already exists. Please try again.\n");
            return;
        }
    }

    printf("Enter Role (Student/Faculty/Admin): ");
    scanf("%s", role);

    printf("Create Password: ");
    getPassword(password);
    printf("Confirm Password: ");
    getPassword(confirmPassword);

    if (strcmp(password, confirmPassword) != 0) {
        printf("\nPasswords do not match. Please try again.\n");
        return;
    }

    if (!isStrongPassword(password)) {
        printf("\nPassword must include uppercase, lowercase, digit, and special character.\n");
        return;
    }

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    strcpy(users[userCount].rollNo, rollNo);
    strcpy(users[userCount].role, role);
    userCount++;

    printf("\nUser added successfully! You can now log in.\n");
}

// Function to handle password reset
void forgotPassword() {
    char rollNo[ROLLNO_LEN], newPassword[PASSWORD_LEN], confirmPassword[PASSWORD_LEN];
    int found = 0;

    system("cls");
    printHeader("Forgot Password");

    printf("\nEnter Roll Number: ");
    scanf("%s", rollNo);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].rollNo, rollNo) == 0) {
            found = 1;
            printf("Enter New Password: ");
            getPassword(newPassword);
            printf("Confirm New Password: ");
            getPassword(confirmPassword);

            if (strcmp(newPassword, confirmPassword) == 0) {
                strcpy(users[i].password, newPassword);
                printf("\nPassword reset successfully!\n");
            } else {
                printf("\nPasswords do not match. Please try again.\n");
            }
            return;
        }
    }

    if (!found) printf("\nRoll Number not found. Please try again.\n");
}

// Admin-specific menu
void adminMenu() {
    int choice;
    do {
        printf("\n1. View Users");
        printf("\n2. Delete User");
        printf("\n3. Logout");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewUsers();
                break;
            case 2:
                deleteUser();
                break;
            case 3:
                printf("\nLogging out...\n");
                return;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    } while (1);
}

// View all registered users
void viewUsers() {
    printf("\nRegistered Users:\n");
    for (int i = 0; i < userCount; i++) {
        printf("%d. %s (Roll No: %s, Role: %s)\n", i + 1, users[i].username, users[i].rollNo, users[i].role);
    }
}

// Delete a user
void deleteUser() {
    char rollNo[ROLLNO_LEN];
    printf("\nEnter Roll Number of user to delete: ");
    scanf("%s", rollNo);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].rollNo, rollNo) == 0) {
            for (int j = i; j < userCount - 1; j++) {
                users[j] = users[j + 1];
            }
            userCount--;
            printf("\nUser deleted successfully.\n");
            return;
        }
    }

    printf("\nUser not found.\n");
}

// Save user data to file
void saveUsersToFile() {
    FILE *file = fopen("users.dat", "wb");
    if (!file) {
        printf("\nError saving user data!\n");
        return;
    }
    fwrite(&userCount, sizeof(int), 1, file);
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
}

// Load user data from file
void loadUsersFromFile() {
    FILE *file = fopen("users.dat", "rb");
    if (!file) return;
    fread(&userCount, sizeof(int), 1, file);
    fread(users, sizeof(User), userCount, file);
    fclose(file);
}