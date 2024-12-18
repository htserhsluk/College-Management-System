#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
#include <time.h>
#define GREEN "\033[32m"      // Green color
#define RESET "\033[0m"       // Reset to default

char *catalog[15] = {
    "Math1",
    "C",
    "Python",
    "DSA",
    "Algorithms",
    "OS",
    "DBMS",
    "CN",
    "SE",
    "ML",
    "AI",
    "DM",
    "Algebra",
    "Calculus",
    "Cyber"
};

struct Data{
    char rollnum[50];
    char pwd[50];
    char student_name[100];
    char gender;
    char dob[11];
    int room_number;
    float fees_remaining;
    float attendance;
    char courses[200];
};

struct Node{
    struct Data d;
    struct Node *next;
};

struct Data d;
struct Node *ptr = NULL;

void deleteNode(struct Node** ptr, char rollnum[]) {
    struct Node* temp = *ptr;
    struct Node* prev = NULL;

    // If the head node itself holds the roll number
    if (temp != NULL && strcmp(temp->d.rollnum, rollnum) == 0) {
        *ptr = temp->next; // Change head
        free(temp); // Free old head
        printf("Student with roll number %s deleted.\n", rollnum);
        return;
    }

    // Search for the roll number
    while (temp != NULL && strcmp(temp->d.rollnum, rollnum) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // If the roll number was not found
    if (temp == NULL) {
        // printf("Student with roll number %s not found.\n", rollnum);
        return;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;
    free(temp); // Free memory
    printf("Student with roll number %s deleted.\n", rollnum);
}

void add_student() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[10] = "localhost", user[5] = "root", password[11] = "kulshresth", database[10] = "project";
    char query[1024], query1[1024], rollnum[50], pwd[50], student_name[100], gender, dob[11], courses[200];
    int room_number;
    float fees_remaining, attendance, mark;
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


	struct Node *temp = malloc(sizeof(struct Node));
	strcpy(temp->d.rollnum,d.rollnum);
    strcpy(temp->d.pwd,d.pwd);
    strcpy(temp->d.student_name,d.student_name);
    temp->d.gender = d.gender;
    strcpy(temp->d.dob,d.dob);
	temp->d.room_number = d.room_number;
	temp->d.fees_remaining = d.fees_remaining;
    temp->d.attendance = d.attendance;
    strcpy(temp->d.courses,d.courses);

	temp->next = NULL;
	if (ptr == NULL){
		ptr = temp;
	}
	else{
		struct Node *add = ptr;
		while (add->next != NULL){
			add = add->next;
		}
		add->next = temp;
	}

    // Formulate the SQL query
    snprintf(query, 1024, 
        "INSERT INTO Students VALUES ('%s', '%s', '%s', '%c', '%s', %d, %.2f, %.1f, '%s')",
        rollnum, pwd, student_name, gender, dob, room_number, fees_remaining, attendance, courses);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Insert query error: %s\n", mysql_error(conn));
        exit(1);
    }
    for (int i = 0; i < 15; i++) {
        if (strstr(courses, catalog[i])) {
            mark = ((float)rand() / RAND_MAX) * 100.0;
            snprintf(query1, 1024, "INSERT INTO %s VALUES ('%s', %f)", catalog[i], rollnum, mark);
            // Execute the query
            if (mysql_query(conn, query1)) {
                fprintf(stderr, "Insert query1 error: %s\n", mysql_error(conn));
                exit(1);
            }
        }
    }

    mysql_close(conn);
}

void add_prof() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[10] = "localhost", user[5] = "root", password[11] = "kulshresth", database[10] = "project";
    char query[1024], username[50], pwd[50], prof_name[100], course[50];
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
    char server[10] = "localhost", user[5] = "root", password[11] = "kulshresth", database[10] = "project";
    char retrieve[9][20] = {"Roll No.", "Password", "Name", "Gender", "DOB", "Room No.", "Fees pending", "Attendance", "Courses"};
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        
        struct Node *print = ptr;
        while (print != NULL){
            printf("Roll Number: %s, Password: %s, Student Name: %s, Gender: %c, DOB: %s, Room No.: %d, Fees Remaining: %f, Attendance: %f, Courses: %s\n",print->d.rollnum,print->d.pwd,print->d.student_name,print->d.gender,print->d.dob,print->d.room_number,print->d.fees_remaining,print->d.attendance,print->d.courses);
            print = print->next;
        }        

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
        for (int i = 0; i < num_fields - 1; i++) {
            printf(GREEN "%s: " RESET, retrieve[i]);
            printf("%s, ", row[i] ? row[i] : "NULL"); // Print column values
        }
        printf(GREEN "%s: " RESET, retrieve[num_fields - 1]);
        printf("%s\n", row[num_fields - 1] ? row[num_fields - 1] : "NULL");
    }
    mysql_free_result(res);
    mysql_close(conn);
}

void retrieve_profs() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[10] = "localhost", user[5] = "root", password[11] = "kulshresth", database[10] = "project";
    char retrieve[4][20] = {"Username", "Password", "Name", "Course"};
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
            printf(GREEN "%s: " RESET, retrieve[i]);
            printf("%s, ", row[i] ? row[i] : "NULL");
        }
        printf(GREEN "%s: " RESET, retrieve[num_fields - 1]);
        printf("%s\n", row[num_fields - 1] ? row[num_fields - 1] : "NULL");
    }
    mysql_free_result(res);
    mysql_close(conn);
}

void profs_usernames(char *username, char professor_data[100][4][50]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[10] = "localhost", user[5] = "root", password[11] = "kulshresth", database[10] = "project", query[1024];
    int index = 0;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    snprintf(query, 1024, "SELECT * FROM Professors WHERE username = '%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Result storage error: %s\n", mysql_error(conn));
        exit(1);
    }

    while ((row = mysql_fetch_row(res)) && index < 100) {
        strncpy(professor_data[index][0], row[0], 49); // Username
        professor_data[index][0][49] = '\0'; // Null-terminate
        strncpy(professor_data[index][1], row[1], 49); // Password
        professor_data[index][1][49] = '\0'; // Null-terminate
        strncpy(professor_data[index][2], row[2], 49); // Name
        professor_data[index][2][49] = '\0'; // Null-terminate
        strncpy(professor_data[index][3], row[3], 49); // Course
        professor_data[index][3][49] = '\0'; // Null-terminate
        index++;
    }

    mysql_free_result(res);
    mysql_close(conn);
}

void students_usernames(char *username, char student_data[100][5][150]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[10] = "localhost", user[5] = "root", password[11] = "kulshresth", database[10] = "project", query[1024];
    int index = 0;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    snprintf(query, 1024, "SELECT rollnum, password, student_name, courses, attendance FROM Students WHERE rollnum = '%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Result storage error: %s\n", mysql_error(conn));
        exit(1);
    }

    while ((row = mysql_fetch_row(res)) && index < 100) {
        strncpy(student_data[index][0], row[0], 49); // Username
        student_data[index][0][49] = '\0'; // Null-terminate
        strncpy(student_data[index][1], row[1], 49); // Password
        student_data[index][1][49] = '\0'; // Null-terminate
        strncpy(student_data[index][2], row[2], 49); // Name
        student_data[index][2][49] = '\0'; // Null-terminate
        strncpy(student_data[index][3], row[3], 149); // Courses
        student_data[index][3][149] = '\0'; // Null-terminate
        strncpy(student_data[index][4], row[4], 149); // Courses
        student_data[index][4][5] = '\0'; // Null-terminate
        index++;
    }

    mysql_free_result(res);
    mysql_close(conn);
}

void remove_student() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[10] = "localhost", user[5] = "root", password[11] = "kulshresth", database[10] = "project";
    char query[1024], rollnum[50], pwd[50];
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter roll number of student to be removed from records: ");
    scanf("%s", rollnum);

    deleteNode(&ptr, rollnum);

    // Formulate the SQL query
    snprintf(query, 1024, "DELETE FROM Students WHERE rollnum = '%s'", rollnum);

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
    char server[10] = "localhost", user[5] = "root", password[11] = "kulshresth", database[10] = "project";
    char query[1024], username[50];
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

int marks(float x, char prof_course[50]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[10] = "localhost", user[5] = "root", password[11] = "kulshresth", database[10] = "project", query[1024];
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
    snprintf(query, 1024, "SELECT * FROM %s WHERE marks >= %f", prof_course, x);
    if (mysql_query(conn, query)) {
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
        printf(GREEN "Roll No.: " RESET);
        printf("%s\t", row[0]); // Print column values
        printf(GREEN "Marks: " RESET);
        printf("%s\n", row[1]); // Print column values
    }
    mysql_free_result(res);
    mysql_close(conn);
}

void view_fees(char *rnum) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[10] = "localhost", user[5] = "root", password[11] = "kulshresth", database[10] = "project", query[1024];
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    snprintf(query, 1024, "SELECT fees_remaining FROM Students WHERE rollnum = '%s'", rnum);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        exit(1);
    }

    // Store the result set
    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Result storage error: %s\n", mysql_error(conn));
        exit(1);
    }
    printf("Fees pending for %s is ", rnum);
    printf(GREEN "%s\n" RESET, mysql_fetch_row(res)[0]);

    mysql_free_result(res);
    mysql_close(conn);
}

void view_courses(char *rnum) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[10] = "localhost", user[5] = "root", password[11] = "kulshresth", database[10] = "project", query[1024];
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    snprintf(query, 1024, "SELECT courses FROM Students WHERE rollnum = '%s'", rnum);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        exit(1);
    }

    // Store the result set
    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Result storage error: %s\n", mysql_error(conn));
        exit(1);
    }
    printf("%s has courses: ", rnum);
    printf(GREEN "%s\n" RESET, mysql_fetch_row(res)[0]);

    mysql_free_result(res);
    mysql_close(conn);
}

void view_acad_report(char *name, char *rnum, char *courses, char *attendance) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[10] = "localhost", user[5] = "root", password[11] = "kulshresth", database[10] = "project", query[1024], grade[6] = "Grade";
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    printf(GREEN "Name: " RESET);
    printf("%s,\t", name);
    printf(GREEN "Roll No.: " RESET);
    printf("%s,\t", rnum);
    printf(GREEN "Overall Attendance: " RESET);
    printf("%s\n", attendance);
    for (int i = 0; i < 15; i++) {
        if (strstr(courses, catalog[i])) {
            snprintf(query, 1024, "SELECT * FROM Students NATURAL JOIN %s", catalog[i]);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "Query error: %s\n", mysql_error(conn));
                exit(1);
            }
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            if (res == NULL) {
                fprintf(stderr, "Result storage error: %s\n", mysql_error(conn));
                exit(1);
            }
            printf(GREEN "Course: " RESET);
            
            if (strlen(catalog[i]) > 6) {
                printf("%s\t", catalog[i]);
                printf(GREEN "%s: " RESET, grade);
                printf("%s\n", row[9]);
            }
            else {
                printf("%s\t\t", catalog[i]);
                printf(GREEN "%s: " RESET, grade);
                printf("%s\n", row[9]);
            }
        }
    }
    mysql_free_result(res);
    mysql_close(conn);
}