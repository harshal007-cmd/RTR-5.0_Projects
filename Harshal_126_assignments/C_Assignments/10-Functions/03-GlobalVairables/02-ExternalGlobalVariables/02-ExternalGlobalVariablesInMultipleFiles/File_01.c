#include<stdio.h>

extern int global_count;

void change_cnt_one()
{
	global_count += 1;
	printf("change_cnt_one() : Value of global_count in File_01 = %d\n", global_count);

}