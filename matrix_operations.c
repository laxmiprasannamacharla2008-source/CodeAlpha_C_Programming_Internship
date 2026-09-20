#include <stdio.h>

#define MAX 10

void inputMatrix(int matrix[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void displayMatrix(int matrix[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(int a[MAX][MAX], int b[MAX][MAX], int result[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX], int result[MAX][MAX],
                      int r1, int c1, int c2)
{
    int i, j, k;

    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            result[i][j] = 0;

            for (k = 0; k < c1; k++)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void transposeMatrix(int matrix[MAX][MAX], int result[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            result[j][i] = matrix[i][j];
        }
    }
}

int main()
{
    int choice;
    int a[MAX][MAX], b[MAX][MAX], result[MAX][MAX];

    int rows, cols;
    int r1, c1, r2, c2;

    do
    {
        printf("\n\n");
        printf("========================================\n");
        printf("          MATRIX OPERATIONS             \n");
        printf("========================================\n");
        printf("  1. Matrix Addition\n");
        printf("  2. Matrix Multiplication\n");
        printf("  3. Matrix Transpose\n");
        printf("  4. Exit\n");
        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:

                printf("\nEnter number of rows: ");
                scanf("%d", &rows);

                printf("Enter number of columns: ");
                scanf("%d", &cols);

                if (rows <= 0 || rows > MAX || cols <= 0 || cols > MAX)
                {
                    printf("\nInvalid matrix size!\n");
                    break;
                }

                printf("\nEnter elements of Matrix A:\n");
                inputMatrix(a, rows, cols);

                printf("\nEnter elements of Matrix B:\n");
                inputMatrix(b, rows, cols);

                addMatrices(a, b, result, rows, cols);

                printf("\nMatrix A:\n");
                displayMatrix(a, rows, cols);

                printf("\nMatrix B:\n");
                displayMatrix(b, rows, cols);

                printf("\nResult of Addition:\n");
                displayMatrix(result, rows, cols);

                break;

            case 2:

                printf("\nEnter rows of Matrix A: ");
                scanf("%d", &r1);

                printf("Enter columns of Matrix A: ");
                scanf("%d", &c1);

                printf("Enter rows of Matrix B: ");
                scanf("%d", &r2);

                printf("Enter columns of Matrix B: ");
                scanf("%d", &c2);

                if (r1 <= 0 || r1 > MAX || c1 <= 0 || c1 > MAX ||
                    r2 <= 0 || r2 > MAX || c2 <= 0 || c2 > MAX)
                {
                    printf("\nInvalid matrix size!\n");
                    break;
                }

                if (c1 != r2)
                {
                    printf("\nMatrix multiplication is not possible!\n");
                    printf("Columns of Matrix A must equal rows of Matrix B.\n");
                    break;
                }

                printf("\nEnter elements of Matrix A:\n");
                inputMatrix(a, r1, c1);

                printf("\nEnter elements of Matrix B:\n");
                inputMatrix(b, r2, c2);

                multiplyMatrices(a, b, result, r1, c1, c2);

                printf("\nResult of Multiplication:\n");
                displayMatrix(result, r1, c2);

                break;

            case 3:

                printf("\nEnter number of rows: ");
                scanf("%d", &rows);

                printf("Enter number of columns: ");
                scanf("%d", &cols);

                if (rows <= 0 || rows > MAX || cols <= 0 || cols > MAX)
                {
                    printf("\nInvalid matrix size!\n");
                    break;
                }

                printf("\nEnter matrix elements:\n");
                inputMatrix(a, rows, cols);

                transposeMatrix(a, result, rows, cols);

                printf("\nOriginal Matrix:\n");
                displayMatrix(a, rows, cols);

                printf("\nTranspose Matrix:\n");
                displayMatrix(result, cols, rows);

                break;

            case 4:

                printf("\nThank you for using Matrix Operations!\n");
                printf("Program exited successfully.\n");

                break;

            default:

                printf("\nInvalid choice!\n");
                printf("Please enter a number between 1 and 4.\n");
        }

    } while (choice != 4);

    return 0;
}