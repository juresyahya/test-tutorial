#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 60
#define MAX_NAME_LENGTH 50
#define FILE_PATH "StudentScore.csv"
#define RESULT_FILE "student_total_score.csv"

typedef struct {
    int student_id;
    char name[MAX_NAME_LENGTH];
    char gender[10];
    int test_1;
    int test_2;
    int test_3;
    float average_score;
} Student;

void calculate_average_scores(Student students[], int num_students);
void find_students_above_threshold(Student students[], int num_students, int threshold);

int main() {
    FILE *file = fopen(FILE_PATH, "r");
    if (!file) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    Student students[MAX_STUDENTS];
    int num_students = 0;

    // Read data from CSV file
    while (fscanf(file, "%d,%49[^,],%9[^,],%d,%d,%d\n",
                  &students[num_students].student_id,
                  students[num_students].name,
                  students[num_students].gender,
                  &students[num_students].test_1,
                  &students[num_students].test_2,
                  &students[num_students].test_3) == 6) {
        num_students++;
    }

    fclose(file);

    // Calculate average scores
    calculate_average_scores(students, num_students);

    // User input for the threshold
    int threshold;
    printf("Enter the threshold for total scores: ");
    scanf("%d", &threshold);

    // Find students above the threshold and save the result
    find_students_above_threshold(students, num_students, threshold);

    return 0;
}

void calculate_average_scores(Student students[], int num_students) {
    for (int i = 0; i < num_students; i++) {
        students[i].average_score = (float)(students[i].test_1 + students[i].test_2 + students[i].test_3) / 3;
    }
}

void find_students_above_threshold(Student students[], int num_students, int threshold) {
    FILE *result_file = fopen(RESULT_FILE, "w");
    if (!result_file) {
        fprintf(stderr, "Error creating result file.\n");
        exit(1);
    }

    fprintf(result_file, "Student_ID,Student_Name,Total_Score\n");

    for (int i = 0; i < num_students; i++) {
        int total_score = students[i].test_1 + students[i].test_2 + students[i].test_3;

        if (total_score > threshold) {
            fprintf(result_file, "%d,%s,%d\n", students[i].student_id, students[i].name, total_score);
        }
    }

    fclose(result_file);

    printf("Result saved in '%s'\n",RESULT_FILE);
}