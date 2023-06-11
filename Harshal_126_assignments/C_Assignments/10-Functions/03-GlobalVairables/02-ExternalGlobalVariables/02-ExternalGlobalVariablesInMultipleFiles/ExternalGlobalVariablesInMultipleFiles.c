#include<stdio.h>

int global_count = 0;
int main()
{
	void change_cnt();
	void change_cnt_one();
	void change_cnt_two();
	
	printf("\n");

	change_cnt();
	change_cnt_one();
	change_cnt_two();
	return 0;
}

int global_cnt = 0;
void change_cnt()
{
	global_cnt += 1;
	printf("change_cnt() = %d\n", global_cnt);
}

