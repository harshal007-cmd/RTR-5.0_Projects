#include<stdio.h>


void change_cnt_two()
{
	extern int global_count;

	global_count += 1;
	printf("change_cnt_two() : Value of global_count in File_02 = %d\n", global_count);

}
