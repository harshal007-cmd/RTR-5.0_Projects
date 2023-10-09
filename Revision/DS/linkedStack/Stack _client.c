
#include"Stack_server.h"


int main()
{
	struct node* top = NULL;
	int data;
	int choice = '1';

	

	while (choice != '0')
	{
		printf("1.Push\n2.Pop\n3.Top\nn5.IsEmpty?6.Display\n0.End\n");
		
		choice = getch();

		switch (choice)
		{
		case '1':
			printf("Enter data to push\n");
			scanf("%d", &data);
			Push(&top, data);
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
			data = Top(top);

			if (data != INT_MIN)
			{
				printf("Top Elemets is : %d", data);
				
			}
			else
			{
				printf("Stack is Empty\n");
			}

			break;

		case '5':
			if (IsStackEmpty(top))
			{
				printf("Stack is Empty\n");
			}
			else
			{
				printf("Stack is not empty\n");
			}
			break;

		case '6':
			DisplayStack(&top);
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