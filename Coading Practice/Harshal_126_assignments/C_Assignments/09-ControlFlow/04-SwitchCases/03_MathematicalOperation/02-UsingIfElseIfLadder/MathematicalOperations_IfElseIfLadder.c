#include <stdio.h> // for printf()
#include <conio.h> //for getch()


int main(void)
{
    //variable declarations
    int a, b;
    int result;

    char option, option_division;

    //code
    printf("\n\n");

    printf("Enter Value For 'A'    : ");
    scanf("%d", &a);

    printf("Enter Value For 'B'    ; ");
    scanf("%d", &b);

    printf("Enter Option In Character : \n\n");
    printf("'A' or 'a' For Addition : \n");
    printf("'S' or 's' For Subtraction : \n");
    printf("'M' or 'm' For Multiplication : \n");
    printf("'D' or 'd' For Division : \n\n");

    printf("Enter Option:   ");
    option = getch();
    printf("\n\n");

    if (option == 'A' || option == 'a')
    {
        result = a + b;
        printf("Additon of A = %d and B= %d gives result %d !!\n\n", a, b, result);

    }
    else if (option == 'S' || option == 's')
    {
        if (a >= b)
        {
            result = a - b;
            printf("Subtraction of A = %d and B= %d gives result %d !!\n\n", a, b, result);

        }
        else
        {
            result = b - a;
            printf("Subtraction of B = %d and A = %d gives result %d !!\n\n", b, a, result);

        }
        
    }
    else if (option == 'M' || option == 'm')
    {
        result = a * b;
        printf("Multiplication of A = %d and B= %d gives result %d !!\n\n", a, b, result);

    }
    else if (option == 'D' || option == 'd')
    {
        printf("Enter Option In Char : \n\n");
        printf(" Q or q or '/' for quotient upon  Division: \n");
        printf("R or r or %% for remonder upon Division: \n");

        printf("Enter Option: ");
        option_division = getch();
        printf("\n\n");

        if (option_division == 'Q' || option_division == 'q' || option_division == '/')
        {
            if (a >= b)
            {
                result = a / b;
                printf("Division of A = %d by B = %d gives Quotient = %d !!\n", a, b, result);
            }
            else
            {
                result = b / a;
                printf("Division of B = %d by A = %d gives Quotient = %d !!\n", b, a, result);

            }
        }
        else if (option_division == 'R' || option_division == 'r' || option_division == '%')
        {
            if (a >= b)
            {
                result = a % b;
                printf("Division of A = %d by B = %d gives reminder = %d !!\n", a, b, result);
            }
            else
            {
                result = b % a;
                printf("Division of B = %d by A = %d gives reminder = %d !!\n", b, a, result);

            }

        }
        else
            printf("Invalid Char %c Entered for division !! try again...\n\n", option_division);

    }
    else
        printf("Invalid Char %c entered !! try again...\n\n", option);

    printf("If else if else ladder done !!\n\n");


    return 0;
}