#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

struct Student
{
    int rollNo;
    char name[50];
    int age;
    char course[50];
    float marks;
};

void addStudent();
void deleteStudent();
void updateStudent();
void searchStudent();
void displayStudents();
void clearInputBuffer();

void clearInputBuffer()
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

void addStudent()
{
    FILE *file;
    struct Student student;

    printf("\n========================================\n");
    printf("             ADD STUDENT                \n");
    printf("========================================\n");

    printf("Enter Roll Number: ");
    scanf("%d", &student.rollNo);
    clearInputBuffer();

    printf("Enter Student Name: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &student.age);
    clearInputBuffer();

    printf("Enter Course: ");
    fgets(student.course, sizeof(student.course), stdin);
    student.course[strcspn(student.course, "\n")] = '\0';

    printf("Enter Marks: ");
    scanf("%f", &student.marks);
    clearInputBuffer();

    file = fopen(FILE_NAME, "ab");

    if (file == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    fwrite(&student, sizeof(struct Student), 1, file);
    fclose(file);

    printf("\nStudent added successfully!\n");
}

void deleteStudent()
{
    FILE *file;
    FILE *tempFile;

    struct Student student;

    int rollNo;
    int found = 0;

    printf("\n========================================\n");
    printf("            DELETE STUDENT              \n");
    printf("========================================\n");

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &rollNo);
    clearInputBuffer();

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    tempFile = fopen("temp.dat", "wb");

    if (tempFile == NULL)
    {
        fclose(file);
        printf("\nError creating temporary file.\n");
        return;
    }

    while (fread(&student, sizeof(struct Student), 1, file))
    {
        if (student.rollNo == rollNo)
        {
            found = 1;
        }
        else
        {
            fwrite(&student, sizeof(struct Student), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
    {
        printf("\nStudent deleted successfully!\n");
    }
    else
    {
        printf("\nStudent not found.\n");
    }
}

void updateStudent()
{
    FILE *file;
    struct Student student;

    int rollNo;
    int found = 0;

    printf("\n========================================\n");
    printf("             UPDATE STUDENT             \n");
    printf("========================================\n");

    printf("Enter Roll Number to Update: ");
    scanf("%d", &rollNo);
    clearInputBuffer();

    file = fopen(FILE_NAME, "rb+");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    while (fread(&student, sizeof(struct Student), 1, file))
    {
        if (student.rollNo == rollNo)
        {
            found = 1;

            printf("\nEnter New Student Name: ");
            fgets(student.name, sizeof(student.name), stdin);
            student.name[strcspn(student.name, "\n")] = '\0';

            printf("Enter New Age: ");
            scanf("%d", &student.age);
            clearInputBuffer();

            printf("Enter New Course: ");
            fgets(student.course, sizeof(student.course), stdin);
            student.course[strcspn(student.course, "\n")] = '\0';

            printf("Enter New Marks: ");
            scanf("%f", &student.marks);
            clearInputBuffer();

            fseek(file, -(long)sizeof(struct Student), SEEK_CUR);

            fwrite(&student, sizeof(struct Student), 1, file);

            printf("\nStudent updated successfully!\n");

            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nStudent not found.\n");
    }
}

void searchStudent()
{
    FILE *file;
    struct Student student;

    int rollNo;
    int found = 0;

    printf("\n========================================\n");
    printf("             SEARCH STUDENT             \n");
    printf("========================================\n");

    printf("Enter Roll Number to Search: ");
    scanf("%d", &rollNo);
    clearInputBuffer();

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    while (fread(&student, sizeof(struct Student), 1, file))
    {
        if (student.rollNo == rollNo)
        {
            printf("\n----------------------------------------\n");
            printf("Student Found!\n");
            printf("----------------------------------------\n");

            printf("Roll Number : %d\n", student.rollNo);
            printf("Name        : %s\n", student.name);
            printf("Age         : %d\n", student.age);
            printf("Course      : %s\n", student.course);
            printf("Marks       : %.2f\n", student.marks);

            printf("----------------------------------------\n");

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nStudent not found.\n");
    }
}

void displayStudents()
{
    FILE *file;
    struct Student student;

    int count = 0;

    printf("\n========================================\n");
    printf("          ALL STUDENT RECORDS           \n");
    printf("========================================\n");

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    while (fread(&student, sizeof(struct Student), 1, file))
    {
        printf("\nStudent %d\n", ++count);

        printf("----------------------------------------\n");
        printf("Roll Number : %d\n", student.rollNo);
        printf("Name        : %s\n", student.name);
        printf("Age         : %d\n", student.age);
        printf("Course      : %s\n", student.course);
        printf("Marks       : %.2f\n", student.marks);
        printf("----------------------------------------\n");
    }

    fclose(file);

    if (count == 0)
    {
        printf("No student records available.\n");
    }
    else
    {
        printf("\nTotal Students: %d\n", count);
    }
}

int main()
{
    int choice;

    do
    {
        printf("\n\n");
        printf("========================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM        \n");
        printf("========================================\n");

        printf("  1. Add Student\n");
        printf("  2. Delete Student\n");
        printf("  3. Update Student\n");
        printf("  4. Search Student\n");
        printf("  5. Display All Students\n");
        printf("  6. Exit\n");

        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                deleteStudent();
                break;

            case 3:
                updateStudent();
                break;

            case 4:
                searchStudent();
                break;

            case 5:
                displayStudents();
                break;

            case 6:
                printf("\nThank you for using Student Management System!\n");
                printf("Program exited successfully.\n");
                break;

            default:
                printf("\nInvalid choice!\n");
                printf("Please enter a number between 1 and 6.\n");
        }

    } while (choice != 6);

    return 0;
}
