#include<stdio.h>

int main()
{
	int a = 10;
	void change_count(void);

	printf("\n\n");
	printf("A = %d\n\n", a);

	change_count();
	change_count();
	change_count();
	return 0;
}

void change_count()
{
	int local_count = 0;
	local_count += 1;
	printf("Local count = %d\n", local_count);
}
