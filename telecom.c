#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct subscriber
{
    char phonenumber[20];
    char name[50];
    float amount;
};

void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();
void searchrecords();
void payment();

int main()
{
    int password;
    char choice;

    printf("\n\n\n\n\n\n\n\n\n**********");
    printf("\n\t\t---WELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM---");
    printf("\n\t\t********");

    while (1)
    {
        printf("\n enter\n A : for adding new records.\n L : for list of records");
        printf("\n M : for modifying records.\n P : for payment");
        printf("\n S : for searching records.");
        printf("\n D : for deleting records.\n E : for exit\n");
        choice = toupper(getchar());
        getchar();

        switch (choice)
        {
            case 'P':
                payment();
                break;
            case 'A':
                addrecords();
                break;
            case 'L':
                listrecords();
                break;
            case 'M':
                modifyrecords();
                break;
            case 'S':
                searchrecords();
                break;
            case 'D':
                deleterecords();
                break;
            case 'E':
                printf("\n\n\t\t\t\tTHANK YOU");
                printf("\n\n\n\n\n:\n\tFOR USING OUR SERVICE");
                exit(0);
                break;
            default:
                printf("Incorrect Input");
                printf("\nAny key to continue");
                getchar();
        }
    }
}

void addrecords()
{
    FILE *f;
    struct subscriber s;
    char test;
    f = fopen("file.ojs", "ab+");
    if (f == NULL)
    {
        f = fopen("file.ojs", "wb+");
        printf("Please wait while we configure your computer.\n");
        printf("Press Enter key to continue.\n");
        getchar();
    }
    while (1)
    {
        printf("\033[H\033[2J"); // Clear screen
        printf("\n Enter phone number:");
        scanf("%s", s.phonenumber);
        printf("\n Enter name:");
        fflush(stdin);
        scanf(" %[^\n]", s.name);
        printf("\n Enter amount:");
        scanf("%f", &s.amount);
        fwrite(&s, sizeof(s), 1, f);
        fflush(stdin);
        printf("\033[H\033[2J"); // Clear screen
        printf("1 record successfully added\n");
        printf("Press Enter key to continue, or 'E' key to add another record:\n");
        test = getchar();
        if (test == '\n')
            continue;
        if (test == 'E' || test == 'e')
            break;
    }
    fclose(f);
}


void listrecords()
{
    FILE *f;
    struct subscriber s;

    f = fopen("file.ojs", "rb");
    if (f == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    printf("Phone Number\t\tUser Name\t\t\tAmount\n");
    for (int i = 0; i < 79; i++)
    {
        printf("-");
    }
    printf("\n");

    while (fread(&s, sizeof(s), 1, f) == 1)
    {
        printf("%-10s\t\t%-20s\t\tRs. %.2f /-\n", s.phonenumber, s.name, s.amount);
    }

    for (int i = 0; i < 79; i++)
    {
        printf("-");
    }
    printf("\n");

    fclose(f);
}

void deleterecords()
{
    FILE *f, *t;
    struct subscriber s;
    char phonenumber[20];
    int flag = 0;

    t = fopen("temp.ojs", "w+");
    if (t == NULL)
    {
        printf("Failed to create temporary file.\n");
        return;
    }

    f = fopen("file.ojs", "rb");
    if (f == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    printf("Enter the phone number to be deleted from the Database: ");
    scanf("%s", phonenumber);

    while (fread(&s, sizeof(s), 1, f) == 1)
    {
        if (strcmp(s.phonenumber, phonenumber) == 0)
        {
            flag = 1;
            continue;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, t);
        }
    }

    if (flag == 0)
    {
        printf("Phone number \"%s\" not found.\n", phonenumber);
        remove("file.ojs");
        rename("temp.ojs", "file.ojs");
        fclose(f);
        fclose(t);
        return;
    }

    remove("file.ojs");
    rename("temp.ojs", "file.ojs");

    printf("The Number %s Successfully Deleted!!!!\n", phonenumber);

    fclose(f);
    fclose(t);
}

void searchrecords()
{
    FILE *f;
    struct subscriber s;
    char phonenumber[20];
    int flag = 0;

    f = fopen("file.ojs", "rb");
    if (f == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    printf("Enter Phone Number to search in our database: ");
    scanf("%s", phonenumber);

    while (fread(&s, sizeof(s), 1, f) == 1)
    {
        if (strcmp(s.phonenumber, phonenumber) == 0)
        {
            flag = 1;

            printf("\nRecord Found\n");
            printf("Phone Number: %s\n", s.phonenumber);
            printf("Name: %s\n", s.name);
            printf("Amount: Rs. %.2f\n", s.amount);

            break;
        }
    }

    if (flag == 0)
    {
        printf("Requested Phone Number not found in our database.\n");
    }

    fclose(f);
}

void modifyrecords()
{
    FILE *f;
    struct subscriber s;
    char phonenumber[20];
    long int size = sizeof(s);
    int flag = 0;

    f = fopen("file.ojs", "rb+");
    if (f == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    printf("Enter phone number of the subscriber to modify: ");
    scanf("%s", phonenumber);
    getchar();

    while (fread(&s, sizeof(s), 1, f) == 1)
    {
        if (strcmp(s.phonenumber, phonenumber) == 0)
        {
            flag = 1;

            printf("\n Enter phone number: ");
            scanf("%s", s.phonenumber);
            printf("\n Enter name: ");
            getchar();
            scanf("%[^\n]", s.name);
            printf("\n Enter amount: ");
            scanf("%f", &s.amount);

            fseek(f, -size, SEEK_CUR);
            fwrite(&s, sizeof(s), 1, f);

            break;
        }
    }

    fclose(f);

    if (flag == 0)
    {
        printf("Phone number \"%s\" not found.\n", phonenumber);
    }
    else
    {
        printf("Record modified successfully.\n");
    }
}

void payment()
{
    FILE *f;
    struct subscriber s;
    char phonenumber[20];
    int flag = 0;
    float amount;

    f = fopen("file.ojs", "rb+");
    if (f == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    printf("Enter the phone number for payment: ");
    scanf("%s", phonenumber);
    getchar();

    while (fread(&s, sizeof(s), 1, f) == 1)
    {
        if (strcmp(s.phonenumber, phonenumber) == 0)
        {
            flag = 1;

            printf("Phone Number: %s\n", s.phonenumber);
            printf("Name: %s\n", s.name);
            printf("Current Amount: Rs. %.2f\n", s.amount);
            printf("Enter amount to pay: ");
            scanf("%f", &amount);

            s.amount -= amount;
            fseek(f, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, f);

            printf("Payment successful. Updated amount: Rs. %.2f\n", s.amount);
            break;
        }
    }

    fclose(f);

    if (flag == 0)
    {
        printf("Phone number \"%s\" not found.\n", phonenumber);
    }
}

