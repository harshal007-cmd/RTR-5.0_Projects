#include<stdio.h>

int main(void)
{
	printf("\n\n");

	printf("Going to next line...using \\n escape sequence!!\n\n");
	printf("Using \t Horizontal \t Tab \t \\t Escape Sequence!!\n\n");
	printf("\'This is Single Quoted Output\' Done using \\\'\\\' Escape Squence\n\n");
	printf("\"This is Double Quoted Output\" Done using \\\"\\\" Escape Squence\n\n");
	printf("BACKSPACE Turned To BACKSPACE\b using Escape Sequence \\b\n\n");
	
	printf("\r Using Carriage return \\r Escape Sequence\n");
	printf("Using \r Carriage return \\r Escape Sequence\n");
	printf("Using Carriage return \r \\r Escape Sequence\n\n");


	printf("Using \x41 with \\xhh Escape Sequence \n\n");
	printf("Using \102 with \\ooo Escape Sequence \n\n");

	return 0;
}

