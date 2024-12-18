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

void deleteNode(struct Node **ptr, char rollnum[]);
void add_student();
void add_prof();
void retrieve_students();
void retrieve_profs();
void profs_usernames(char *username, char professor_data[100][4][50]);
void students_usernames(char *username, char student_data[100][5][150]);
void remove_student();
void remove_prof();
int marks(float x, char prof_course[50]);
void view_fees(char *rnum);
void view_courses(char *rnum);
void view_acad_report(char *name, char *rnum, char *courses, char *attendance);