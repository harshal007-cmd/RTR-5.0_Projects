#include<stdio.h>

int main()
{
	void change_cnt();
	extern int global_cnt;

	printf("\n\nValue of global count before change_cnt() = %d\n", global_cnt);
	change_cnt();
	printf("\n\nValue of global count after change_cnt() = %d\n", global_cnt);
	printf("\n");
	return 0;
}

int global_cnt = 0;
void change_cnt()
{
	global_cnt = 10;
	printf("Value of global count in change_cnt() = %d\n", global_cnt);
}
