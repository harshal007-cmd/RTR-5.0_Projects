#include<iostream>
using namespace std;
int main()
{
	char str[] = "Harshal";
	cout << str;
	int len = sizeof(str)/sizeof(char);
	char str1[20]={};
	printf("Len = %d\n",len);
	int i,j;
	for(i=len-1,  j=0; i>=0,j<len; i--,j++)
	{
		str1[j] = str[i];
		//cout <<i <<" " << j << "\n";
		printf("%c", str1[j]);
	}
	cout << str1;
	printf("%s", str1);
	//cout << str1 << endl;
	
	
	return 0;
}