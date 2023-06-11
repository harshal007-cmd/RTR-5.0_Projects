#include<stdio.h>

int global_count = 0;

int main(void)
{
	void change_count_one(void);
	void change_count_two(void);
	void change_count_three(void);

	printf("\n");

	printf("main() : value of global_count = %d\n", global_count);

	change_count_one();
	change_count_two();
	change_count_three();

	printf("\n");
	return 0;
}

void change_count_one()
{
	global_count = 100;
	printf("change_count_one() : Value of global_count = %d\n", global_count);
}

void change_count_two()
{
	global_count = global_count + 1;
	printf("change_count_two() : Value of global_count = %d\n", global_count);
}

void change_count_three()
{
	global_count = global_count + 10;
	printf("change_count_three() : Value of global_count = %d\n", global_count);
}
