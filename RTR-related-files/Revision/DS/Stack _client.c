
#include"Stack.h"


int main()
{
	struct stack* st = NULL;
	int data;
	int choice = '1';

	st = CreateStack();

	while (choice != '0')
	{
		printf("1.Push\n2.Pop\n3.Top\n4.IsFull?\n5.IsEmpty?6.Display\n0.End\n");
		
		choice = getch();

		switch (choice)
		{
		case '1':
			printf("Enter data to push\n");
			scanf("%d", &data);
			Push(st, data);
			printf("Stack elements are\n");
			DisplayStack(st);
			break;
	
		case '2':
			data = Pop(st);

			if (data != INT_MIN)
			{
				printf("Deleted Elemets : %d", data);
				printf("Stack Elements are : \n");
				DisplayStack(st);
			}
			else
			{
				printf("Stack is Empty\n");
			}
			
			break;

		case '3':
			data = Top(st);

			if (data != INT_MIN)
			{
				printf("Top Elemets is : %d", data);
				
			}
			else
			{
				printf("Stack is Empty\n");
			}

			break;

		case '4':
			if (IsStackFull(st))
			{
				printf("Stack is Full\n");
			}
			else
			{
				printf("Stack is not full\n");
			}
			break;

		case '5':
			if (IsStackEmpty(st))
			{
				printf("Stack is Empty\n");
			}
			else
			{
				printf("Stack is not empty\n");
			}
			break;

		case '6':
			DisplayStack(st);
			break;

		case '0':
			DeleteStack(st);
			break;
		default:
			printf("Invalid entery, try again\n");
			break;

		}
	}
	return 0;
}