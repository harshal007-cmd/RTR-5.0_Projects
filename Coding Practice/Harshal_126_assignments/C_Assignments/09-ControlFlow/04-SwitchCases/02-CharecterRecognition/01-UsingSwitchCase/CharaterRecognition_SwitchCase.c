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

	switch (ch)
	{
	case 'A':
	case 'a':
	
	case 'E':
	case 'e':
	
	case 'I':
	case 'i':
	
	case 'O':
	case 'o':
	
	case 'U':
	case 'u':
		printf("Chareter \'%c\' Entered by you, Is A VOWEL CHARACTER from the english aphabet !!\n\n", ch);
		break;
	default:
		ch_value = (int)ch;

		if ((ch_value >= CHAR_ALPHABET_UPEER_CASE_BEGINNING && ch_value <= CHAR_ALPHABET_UPPER_CASE_ENDING) || (ch_value >= CHAR_ALPHABET_LOWER_CASE_BEGINNING && ch_value <= CHAR_ALPHABET_LOWER_CASE_ENDING))
		{
			printf("Charater \'%c\' entered by you, Is a Consonent  !! \n", ch);
		}
		else if(ch_value >=CHAR_DIGIT_BEGINNING && ch_value <=CHAR_DIGIT_ENDING)
		{
			printf("Charater \'%c\' entered by you, Is Digit char !!\n", ch);
		}
		else
		{
			printf("Charater \'%c\' entered by you, Is Special char !!\n", ch);
		}

		break;
	}
	printf("Switch case block complete !!\n");

	return 0;
}
