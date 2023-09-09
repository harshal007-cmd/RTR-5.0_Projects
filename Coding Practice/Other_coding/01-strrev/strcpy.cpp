#include<iostream>
using namespace std;
int main()
{
	char str[] = "Harshal";
	int len = sizeof(str)/sizeof(char);
	char str1[20];
	printf("Len = %d\n",len);
	int i,j;
	for(i=len-1,  j=0; i>=0,j<len-1; i--,j++)
	{
		printf("%c",str[i]);
		//str1[j] = str[i];
		
	}
	printf("%s",str1);
	
	return 0;
}