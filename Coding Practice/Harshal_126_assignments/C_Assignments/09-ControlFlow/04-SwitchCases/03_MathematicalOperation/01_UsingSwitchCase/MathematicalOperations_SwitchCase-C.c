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

    switch (option)
    {
    case 'A':
    case 'a':

        result = a + b;
        printf("Additon of A = %d and B= %d gives result %d !!\n\n", a, b, result);
        break;

    case 'S':
    case 's':
        if (a >= b)
        {
            result = a - b;
            printf("Subtraction of A = %d and B= %d gives result %d !!\n\n", a, b, result);

        }
        else
        {
            result = b - a;
            printf("Subtraction of A = %d and B= %d gives result %d !!\n\n", a, b, result);

        }
        break;

    case 'M':
    case 'm':
        result = a * b;
        printf("Multiplication of A = %d and B= %d gives result %d !!\n\n", a, b, result);
        break;
    
    case 'D':
    case 'd':
        printf("Enter Option In Char : \n\n");
        printf(" Q or q or '/' for quotient upon  Division: \n");
        printf("R or r or %% for remonder upon Division: \n");

        printf("Enter Option: ");
        option_division = getch();

        switch (option_division)
        {
        case 'Q':
        case 'q':
        case '/':
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
            break;

        case 'R':
        case 'r':
        case '%':
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
            break;

        default:
            printf("Invalid Char %c Entered for Division..\n\n", option_division);
            break;
        }

    default:
        printf("Invalid Char %c Entered !! try again..\n\n", option);
        break;
    }
    printf("Switch case complete !!\n");
    return 0;
}









