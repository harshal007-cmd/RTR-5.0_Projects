#include<stdio.h>
#include<conio.h>

#define CHAR_ALPHABET_UPEER_CASE_BEGINNING 65
#define CHAR_ALPHABET_UPPER_CASE_ENDING 90

#define CHAR_ALPHABET_LOWER_CASE_BEGINNING 97
#define CHAR_ALPHABET_LOWER_CASE_ENDING 122

#define CHAR_DIGIT_BEGINNING 48
#define CHAR_DIGIT_ENDING 57


int main()
{
	char ch;
	int ch_value;

	printf("\n\n");

	printf("Enter charecter : ");
	ch = getch();

	printf("\n");

	if ((ch == 'A' || ch == 'a') || (ch == 'E' || ch == 'e') || (ch == 'I' || ch == 'i') || (ch == 'O' || ch == 'o') || (ch == 'U' || ch == 'u'))
	{
		printf("Chareter \'%c\' Entered by you, Is A VOWEL CHARACTER from the english aphabet !!\n\n", ch);

	}
	else
	{
		ch_value = (int)ch;

		if ((ch_value >= CHAR_ALPHABET_UPEER_CASE_BEGINNING && ch_value <= CHAR_ALPHABET_LOWER_CASE_ENDING) || (ch_value >= CHAR_ALPHABET_LOWER_CASE_BEGINNING && ch_value <= CHAR_ALPHABET_LOWER_CASE_ENDING))
		{
			printf("Char \'%c\' entered is Consonantr char !! \n\n", ch);
		}
		else if (ch_value >= CHAR_DIGIT_BEGINNING && ch_value <= CHAR_DIGIT_ENDING)
		{
			printf("Charater \'%c\' entered by you, Is Digit char !!\n", ch);
		}
		else
		{
			printf("Charater \'%c\' entered by you, Is Special char !!\n", ch);

		}

	}
	return 0;
}










