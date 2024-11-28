#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>

void add_student() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[100], user[100], password[100], database[10] = "clg_test";
    char query[1024], rollnum[50], pwd[50], student_name[100], gender, dob[11], courses[200];
    int room_number;
    float fees_remaining, attendance;
    printf("Enter host name: ");
    scanf("%s", server);
    printf("Enter SQL user: ");
    scanf("%s", user);
    printf("Enter password: ");
    scanf("%s", password);
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter roll number (username): ");
    scanf("%s", rollnum);

    printf("Enter password: ");
    scanf("%s", pwd);

    printf("Enter student name: ");
    getchar(); // Consume newline character left in buffer
    fgets(student_name, sizeof(student_name), stdin);
    student_name[strcspn(student_name, "\n")] = 0; // Remove newline

    printf("Enter gender (M/F): ");
    scanf("%c", &gender);

    printf("Enter date of birth (YYYY-MM-DD): ");
    scanf("%s", dob);

    printf("Enter room number: ");
    scanf("%d", &room_number);

    printf("Enter fees remaining: ");
    scanf("%f", &fees_remaining);

    printf("Enter attendance percentage: ");
    scanf("%f", &attendance);

    printf("Enter courses (comma-separated): ");
    getchar(); // Consume newline character left in buffer
    fgets(courses, sizeof(courses), stdin);
    courses[strcspn(courses, "\n")] = 0; // Remove newline

    // Formulate the SQL query
    snprintf(query, 1024, 
        "INSERT INTO Students VALUES ('%s', '%s', '%s', '%c', '%s', %d, %.2f, %.1f, '%s')",
        rollnum, pwd, student_name, gender, dob, room_number, fees_remaining, attendance, courses);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Insert query error: %s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

void add_prof() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[100], user[100], password[100], database[10] = "clg_test";
    char query[1024], username[50], pwd[50], prof_name[100], course[20];
    printf("Enter host name: ");
    scanf("%s", server);
    printf("Enter SQL user: ");
    scanf("%s", user);
    printf("Enter password: ");
    scanf("%s", password);
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", pwd);

    printf("Enter professor's name: ");
    getchar(); // Consume newline character left in buffer
    fgets(prof_name, sizeof(prof_name), stdin);
    prof_name[strcspn(prof_name, "\n")] = 0; // Remove newline

    printf("Enter course: ");
    scanf("%s", course);

    // Formulate the SQL query
    snprintf(query, 1024, "INSERT INTO Professors VALUES ('%s', '%s', '%s', '%s')", username, pwd, prof_name, course);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Insert query error: %s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

void retrieve_students() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[100], user[100], password[100], database[10] = "clg_test";
    printf("Enter host name: ");
    scanf("%s", server);
    printf("Enter SQL user: ");
    scanf("%s", user);
    printf("Enter password: ");
    scanf("%s", password);
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_query(conn, "SELECT * FROM Students")) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        exit(1);
    }

    // Store the result set
    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Result storage error: %s\n", mysql_error(conn));
        exit(1);
    }
    int num_fields = mysql_num_fields(res); // Get the number of fields (columns)
    // Fetch each row
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s\t", row[i] ? row[i] : "NULL"); // Print column values
        }
        printf("\n");
    }
    mysql_free_result(res);
    mysql_close(conn);
}

void retrieve_profs() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[100], user[100], password[100], database[10] = "clg_test";
    printf("Enter host name: ");
    scanf("%s", server);
    printf("Enter SQL user: ");
    scanf("%s", user);
    printf("Enter password: ");
    scanf("%s", password);
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_query(conn, "SELECT * FROM Professors")) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        exit(1);
    }

    // Store the result set
    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Result storage error: %s\n", mysql_error(conn));
        exit(1);
    }
    int num_fields = mysql_num_fields(res); // Get the number of fields (columns)
    // Fetch each row
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s\t", row[i] ? row[i] : "NULL"); // Print column values
        }
        printf("\n");
    }
    mysql_free_result(res);
    mysql_close(conn);
}

void remove_student() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[100], user[100], password[100], database[10] = "clg_test";
    char query[1024], rollnum[50], pwd[50];
    printf("Enter host name: ");
    scanf("%s", server);
    printf("Enter SQL user: ");
    scanf("%s", user);
    printf("Enter password: ");
    scanf("%s", password);
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter roll number of student to be removed from records: ");
    scanf("%s", rollnum);

    // Formulate the SQL query
    snprintf(query, 1024, "DELETE FROM Students WHERE username = '%s'", rollnum);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Insert query error: %s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

void remove_prof() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[100], user[100], password[100], database[10] = "clg_test";
    char query[1024], username[50];
    printf("Enter host name: ");
    scanf("%s", server);
    printf("Enter SQL user: ");
    scanf("%s", user);
    printf("Enter password: ");
    scanf("%s", password);
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    printf("Enter username of professor to be removed: ");
    scanf("%s", username);
    // Formulate the SQL query
    snprintf(query, 1024, "DELETE FROM Professors WHERE username = '%s'", username);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Insert query error: %s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}
