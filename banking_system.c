#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCOUNT_FILE "accounts.dat"
#define TRANSACTION_FILE "transactions.txt"

struct Account
{
    int accountNumber;
    char name[50];
    float balance;
};

/* Function declarations */
void createAccount();
void depositMoney();
void withdrawMoney();
void balanceEnquiry();
void displayAccount();
void searchAccount();
void displayTransactions();

int accountExists(int accountNumber);
void recordTransaction(int accountNumber, const char transaction[], float amount);
void clearInputBuffer();


/* Clear unwanted input from keyboard */
void clearInputBuffer()
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* Clear buffer */
    }
}


/* Check whether account number already exists */
int accountExists(int accountNumber)
{
    FILE *file;
    struct Account account;

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(&account, sizeof(struct Account), 1, file))
    {
        if (account.accountNumber == accountNumber)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}


/* Record transaction in transaction file */
void recordTransaction(int accountNumber, const char transaction[], float amount)
{
    FILE *file;

    file = fopen(TRANSACTION_FILE, "a");

    if (file == NULL)
    {
        printf("\nUnable to open transaction file.\n");
        return;
    }

    fprintf(file,
            "Account: %d | Transaction: %s | Amount: %.2f\n",
            accountNumber, transaction, amount);

    fclose(file);
}


/* Create a new bank account */
void createAccount()
{
    FILE *file;
    struct Account account;

    printf("\n========================================\n");
    printf("           CREATE NEW ACCOUNT           \n");
    printf("========================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &account.accountNumber);
    clearInputBuffer();

    if (accountExists(account.accountNumber))
    {
        printf("\nAccount number already exists!\n");
        printf("Please use another account number.\n");
        return;
    }

    printf("Enter Account Holder Name: ");
    fgets(account.name, sizeof(account.name), stdin);

    account.name[strcspn(account.name, "\n")] = '\0';

    if (strlen(account.name) == 0)
    {
        printf("\nName cannot be empty.\n");
        return;
    }

    printf("Enter Initial Deposit: ");
    scanf("%f", &account.balance);
    clearInputBuffer();

    if (account.balance < 0)
    {
        printf("\nInitial deposit cannot be negative.\n");
        return;
    }

    file = fopen(ACCOUNT_FILE, "ab");

    if (file == NULL)
    {
        printf("\nError opening account file.\n");
        return;
    }

    fwrite(&account, sizeof(struct Account), 1, file);
    fclose(file);

    recordTransaction(
        account.accountNumber,
        "Account Created",
        account.balance
    );

    printf("\n----------------------------------------\n");
    printf("Account created successfully!\n");
    printf("----------------------------------------\n");
    printf("Account Number : %d\n", account.accountNumber);
    printf("Account Holder : %s\n", account.name);
    printf("Balance        : %.2f\n", account.balance);
}


/* Deposit money */
void depositMoney()
{
    FILE *file;
    struct Account account;

    int accountNumber;
    float amount;
    int found = 0;

    printf("\n========================================\n");
    printf("             DEPOSIT MONEY              \n");
    printf("========================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    printf("Enter Amount to Deposit: ");
    scanf("%f", &amount);
    clearInputBuffer();

    if (amount <= 0)
    {
        printf("\nAmount must be greater than zero.\n");
        return;
    }

    file = fopen(ACCOUNT_FILE, "rb+");

    if (file == NULL)
    {
        printf("\nNo account records found.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file))
    {
        if (account.accountNumber == accountNumber)
        {
            account.balance += amount;

            fseek(file, -(long)sizeof(struct Account), SEEK_CUR);
            fwrite(&account, sizeof(struct Account), 1, file);

            found = 1;

            recordTransaction(
                accountNumber,
                "Deposit",
                amount
            );

            printf("\nDeposit successful!\n");
            printf("Amount Deposited : %.2f\n", amount);
            printf("New Balance      : %.2f\n", account.balance);

            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nAccount not found.\n");
    }
}


/* Withdraw money */
void withdrawMoney()
{
    FILE *file;
    struct Account account;

    int accountNumber;
    float amount;
    int found = 0;

    printf("\n========================================\n");
    printf("             WITHDRAW MONEY             \n");
    printf("========================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amount);
    clearInputBuffer();

    if (amount <= 0)
    {
        printf("\nAmount must be greater than zero.\n");
        return;
    }

    file = fopen(ACCOUNT_FILE, "rb+");

    if (file == NULL)
    {
        printf("\nNo account records found.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file))
    {
        if (account.accountNumber == accountNumber)
        {
            found = 1;

            if (amount > account.balance)
            {
                printf("\nInsufficient balance!\n");
                printf("Available Balance : %.2f\n", account.balance);

                fclose(file);
                return;
            }

            account.balance -= amount;

            fseek(file, -(long)sizeof(struct Account), SEEK_CUR);
            fwrite(&account, sizeof(struct Account), 1, file);

            recordTransaction(
                accountNumber,
                "Withdrawal",
                amount
            );

            printf("\nWithdrawal successful!\n");
            printf("Amount Withdrawn : %.2f\n", amount);
            printf("New Balance      : %.2f\n", account.balance);

            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nAccount not found.\n");
    }
}


/* Balance enquiry */
void balanceEnquiry()
{
    FILE *file;
    struct Account account;

    int accountNumber;
    int found = 0;

    printf("\n========================================\n");
    printf("             BALANCE ENQUIRY            \n");
    printf("========================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    clearInputBuffer();

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo account records found.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file))
    {
        if (account.accountNumber == accountNumber)
        {
            printf("\n----------------------------------------\n");
            printf("Account Number : %d\n", account.accountNumber);
            printf("Account Holder : %s\n", account.name);
            printf("Current Balance: %.2f\n", account.balance);
            printf("----------------------------------------\n");

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nAccount not found.\n");
    }
}


/* Display complete account details */
void displayAccount()
{
    FILE *file;
    struct Account account;

    int accountNumber;
    int found = 0;

    printf("\n========================================\n");
    printf("           ACCOUNT DETAILS              \n");
    printf("========================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    clearInputBuffer();

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo account records found.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file))
    {
        if (account.accountNumber == accountNumber)
        {
            printf("\n========================================\n");
            printf("             ACCOUNT DETAILS            \n");
            printf("========================================\n");
            printf("Account Number : %d\n", account.accountNumber);
            printf("Account Holder : %s\n", account.name);
            printf("Account Balance: %.2f\n", account.balance);
            printf("========================================\n");

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nAccount not found.\n");
    }
}


/* Search for an account */
void searchAccount()
{
    FILE *file;
    struct Account account;

    int accountNumber;
    int found = 0;

    printf("\n========================================\n");
    printf("              SEARCH ACCOUNT            \n");
    printf("========================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    clearInputBuffer();

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo account records found.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file))
    {
        if (account.accountNumber == accountNumber)
        {
            printf("\nAccount Found!\n");
            printf("----------------------------------------\n");
            printf("Account Number : %d\n", account.accountNumber);
            printf("Account Holder : %s\n", account.name);
            printf("Balance        : %.2f\n", account.balance);
            printf("----------------------------------------\n");

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nAccount not found.\n");
    }
}


/* Display transaction history */
void displayTransactions()
{
    FILE *file;
    char line[200];

    int accountNumber;
    int found = 0;

    printf("\n========================================\n");
    printf("          TRANSACTION HISTORY           \n");
    printf("========================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    clearInputBuffer();

    file = fopen(TRANSACTION_FILE, "r");

    if (file == NULL)
    {
        printf("\nNo transaction records found.\n");
        return;
    }

    printf("\nTransactions for Account %d:\n", accountNumber);
    printf("----------------------------------------\n");

    while (fgets(line, sizeof(line), file))
    {
        int fileAccountNumber;

        if (sscanf(line, "Account: %d", &fileAccountNumber) == 1)
        {
            if (fileAccountNumber == accountNumber)
            {
                printf("%s", line);
                found = 1;
            }
        }
    }

    fclose(file);

    if (!found)
    {
        printf("No transactions found for this account.\n");
    }

    printf("----------------------------------------\n");
}


/* Main function */
int main()
{
    int choice;

    do
    {
        printf("\n\n");
        printf("========================================\n");
        printf("       BANK ACCOUNT MANAGEMENT          \n");
        printf("========================================\n");
        printf("  1. Create Account\n");
        printf("  2. Deposit Money\n");
        printf("  3. Withdraw Money\n");
        printf("  4. Balance Enquiry\n");
        printf("  5. Display Account Details\n");
        printf("  6. Search Account\n");
        printf("  7. Transaction History\n");
        printf("  8. Exit\n");
        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                balanceEnquiry();
                break;

            case 5:
                displayAccount();
                break;

            case 6:
                searchAccount();
                break;

            case 7:
                displayTransactions();
                break;

            case 8:
                printf("\nThank you for using the Banking System!\n");
                printf("Program exited successfully.\n");
                break;

            default:
                printf("\nInvalid choice!\n");
                printf("Please enter a number between 1 and 8.\n");
        }

    } while (choice != 8);

    return 0;
}