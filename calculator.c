#include <stdio.h>

float add(float a, float b)
{
    return a + b;
}

float subtract(float a, float b)
{
    return a - b;
}

float multiply(float a, float b)
{
    return a * b;
}

float divide(float a, float b)
{
    return a / b;
}

int modulus(int a, int b)
{
    return a % b;
}

int main()
{
    int choice;
    float num1, num2;

    do
    {
        printf("\n========================================\n");
        printf("             CALCULATOR\n");
        printf("========================================\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Modulus\n");
        printf("6. Exit\n");
        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4)
        {
            printf("Enter first number: ");
            scanf("%f", &num1);

            printf("Enter second number: ");
            scanf("%f", &num2);
        }

        switch (choice)
        {
            case 1:
                printf("Result: %.2f\n", add(num1, num2));
                break;

            case 2:
                printf("Result: %.2f\n", subtract(num1, num2));
                break;

            case 3:
                printf("Result: %.2f\n", multiply(num1, num2));
                break;

            case 4:
                if (num2 == 0)
                    printf("Error: Cannot divide by zero!\n");
                else
                    printf("Result: %.2f\n", divide(num1, num2));
                break;

            case 5:
            {
                int a, b;

                printf("Enter first integer: ");
                scanf("%d", &a);

                printf("Enter second integer: ");
                scanf("%d", &b);

                if (b == 0)
                    printf("Error: Cannot find modulus with zero!\n");
                else
                    printf("Result: %d\n", modulus(a, b));

                break;
            }

            case 6:
                printf("\nThank you for using Calculator!\n");
                printf("Program exited successfully.\n");
                break;

            default:
                printf("Invalid choice! Please enter 1 to 6.\n");
        }

    } while (choice != 6);

    return 0;
}