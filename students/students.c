/*
This code reads data from a CSV file, organizes that data
and answers basic facts based on the data. Data is related
to names of students and their marks in various subjects.

A simple CSV parser is implemented in a manner specific to
the student data. As an alternative, we can try using
open source CSV parsers.

In this code there are elements of sorting and searching,
handling dates and printing formatted tabular data.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// TODO Make this dynamic based on file content
// first_name,last_name,date_of_birth,sex,maths,sci,social,english,hindi,kannada
#define MAX_LINE_SIZE 1024
#define MAX_STUDENTS 300
#define NUM_COLS 10

typedef enum subjects {
    Maths = 0,
    Science,
    Social,
    English,
    Hindi,
    Kannada,
    NumOfSubjects
} Subjects;

const char *SubjNames[] = {
    "Maths", "Science", "Social", "English", "Hindi", "Kannada"
};

// A+ if >= 91, pass if >= 35
char const * Grades[] = { "A+", "A", "B+", "B", "C", "D", "F" };
int GradeCutOffs[]    = {  91,  81,  71,   61,  51,  35,   0  };

typedef struct student {
    // Read from source
    char first_name[50];
    char last_name[50];
    char date_of_birth[15];
    char sex; // M or F
    int marks[NumOfSubjects];

    // Computed
    int total_marks;
    char const * grades[NumOfSubjects];
    bool has_passed;
} Student;

typedef struct class {
    int num_students;
    Student students[MAX_STUDENTS];
} Class;


float diff_in_years(struct tm *a, struct tm *b) {
    return abs(b->tm_year*12 - a->tm_year*12 + b->tm_mon - a->tm_mon) / 12.0;
}

struct tm parse_date(const char *date_str) {
    struct tm t = {};
    int day, month, year;

    if (sscanf(date_str, "%d/%d/%d", &day, &month, &year) == 3) {
        t.tm_mday = day;
        t.tm_mon = month - 1; // 0: Jan, 11: Dec
        t.tm_year = year - 1900;  // #years since 1900
    }
    
    mktime(&t);
    return t;
}

void parse_csv(Class *cls, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_SIZE];

    fgets(line, sizeof(line), fp); // ignore header row
    while (fgets(line, sizeof(line), fp)) {
        Student *s = cls->students + cls->num_students;
        
        // %[^,]: Matches any character except a comma (reads strings with spaces)
        int matched = sscanf(line, 
            "%[^,],%[^,],%[^,],%c,%d,%d,%d,%d,%d,%d",
            s->first_name, s->last_name, s->date_of_birth, &s->sex,
            &s->marks[Maths], &s->marks[Science], &s->marks[Social],
            &s->marks[English], &s->marks[Hindi], &s->marks[Kannada]);

        if (matched != NUM_COLS) {
            printf("Warning: Row was malformed: %s\n", line);
        }

        cls->num_students++;
    }

    fclose(fp);
}

char const * get_grade(int mark) {
    for (int i = 0; i < sizeof(GradeCutOffs)/sizeof(int); i++) {
        if (mark >= GradeCutOffs[i]) return Grades[i];
    }
    return "F"; // won't come here normally
}

bool has_passed(char const *grades[]) {
    for (int j = 0; j < NumOfSubjects; j++) {
        // Overall failed if failed in at least one subject
        // Hence return false right away
        if (strcmp(grades[j], "F") == 0) return false;
    }
    return true;
}

void analyze_and_print(Class *cls) {
    // Process all students
    for (int i = 0; i < cls->num_students; i++) {
        Student *s = cls->students + i;
        s->total_marks = 0;
        for (int j = 0; j < NumOfSubjects; j++) {
            s->total_marks += s->marks[j];
            s->grades[j] = get_grade(s->marks[j]);
        }
        s->has_passed = has_passed(s->grades);
    }

    // Sex-wise count and average age
    printf("-------------------------\n");
    printf("        Count    Mean Age\n");
    printf("-------------------------\n");
    int num_m = 0, num_f = 0;
    float age_m = 0, age_f = 0;
    time_t now = time(NULL);
    struct tm *today = localtime(&now);
    mktime(today);
    for (int i = 0; i < cls->num_students; i++) {
        struct tm dob = parse_date(cls->students[i].date_of_birth);
        float age = diff_in_years(&dob, today);
        if (cls->students[i].sex == 'M') {
            num_m++;
            age_m += age;
        }
        else {
            num_f++;
            age_f += age;
        }
    }
    age_m /= num_m;
    age_f /= num_f;
    printf(" Boys      %2d       %4.2f\n", num_m, age_m);
    printf("Girls      %2d       %4.2f\n", num_f, age_f);
    printf("\n");

    // Subject-wise grade summary
    int num_grades = sizeof(Grades)/sizeof(char*);
    printf("--------------------------------------\n");
    printf(" Subject  ");
    for (int g = 0; g < num_grades; g++) {
        printf("  %2s", Grades[g]);
    }
    printf("\n");
    printf("--------------------------------------\n");
    for (int j = 0; j < NumOfSubjects; j++) {
        printf("%8s  ", SubjNames[j]);
        int count[num_grades];
        memset(count, 0, sizeof(count));
        for (int i = 0; i < cls->num_students; i++) {
            char const * grade = cls->students[i].grades[j];
            for (int g = 0; g < num_grades; g++) {
                if (strcmp(grade, Grades[g]) == 0) {
                    count[g]++;
                    break;
                }
            }
        }
        for (int g = 0; g < num_grades; g++) {
            printf("  %2d", count[g]);
        }
        printf("\n");
    }
    printf("\n");

    // Subject-wise mean, min and max
    float mean[NumOfSubjects];
    int min[NumOfSubjects], max[NumOfSubjects];
    printf("--------------------------------\n");
    printf("Subject     Mean     Min     Max\n");
    printf("--------------------------------\n");
    for (int j = 0; j < NumOfSubjects; j++) {
        mean[j] = 0; min[j] = 100; max[j] = 0;
        for (int i = 0; i < cls->num_students; i++) {
            int mark = cls->students[i].marks[j];
            mean[j] += mark; // divide later
            if (mark < min[j]) min[j] = mark;
            if (mark > max[j]) max[j] = mark;
        }
        mean[j] /= (float)cls->num_students;
        printf("%7s     %4.1f     %3d     %3d\n",
            SubjNames[j], mean[j], min[j], max[j]);
    }
    printf("\n");
    
    // Top 5 passing students by total marks
    // Inefficient sorting O(N^2)
    Student *toppers[5]; // sorted array of pointers
    printf("---------------------------------------\n");
    printf("#  Name                     Sex   Total\n");
    printf("---------------------------------------\n");
    for (int t = 0; t < sizeof(toppers)/sizeof(Student*); t++) {
        int high_total = 0; // t-th highest
        for (int i = 0; i < cls->num_students; i++) {
            Student *s = cls->students + i;

            // Ignore failed students
            if (!s->has_passed) continue;

            // Ignore students already in toppers
            bool skip = false;
            for (int k = 0; k <= t-1; k++) {
                if (s == toppers[k]) {
                    skip = true;
                    break;
                }
            }
            if (skip) continue;

            if (s->total_marks > high_total) {
                high_total = s->total_marks;
                toppers[t] = s;
            }
        }
        char name[20];
        snprintf(name, 20, "%s %s", toppers[t]->first_name, toppers[t]->last_name);
        printf("%d. %-21s    %3c   %5d\n",
            t+1, name, toppers[t]->sex, toppers[t]->total_marks);
    }
}

int main() {
    Class class12;
    parse_csv(&class12, "student_records.csv");
    analyze_and_print(&class12);
    return 0;
}