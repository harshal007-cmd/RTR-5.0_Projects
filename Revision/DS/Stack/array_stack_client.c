#include"stack_server.h"

int main(void)
{
	int choice = 1;
	struct stack* st = NULL;
	int data;
	st = CreateStack();

	while (choice != 0)
	{
		printf("\n\n1.Push\n2.Pop\n3.Is Empty\n4.Is Full\n5.Display\n0.End\n");
		printf("Enter Your Choice : ");
		printf("\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("Enter Data To be Pushed : ");
			scanf("%d", &data);
			Push(st, data);
			
			printf("\nStack Elements Are :\n");
			DisplayStack(st);
			break;

		case 2:
			data = Pop(st);
			if (data != INT_MIN)
			{
				printf("Removed Element from the stack Is : %d\n", data);
				printf("\nStack Elements Are :\n");
				DisplayStack(st);
			}
			break;

		case 3:
			if (IsStackEmpty(st))
				printf("Stack Is Empty\n");
			else
				printf("stack Is Not Empty\n");
			break;

		case 4:
			if (IsStackFull(st))
				printf("Stack Is Full\n");
			else
				printf("stack Is Not Full\n");
			break;

		case 5:
			printf("Stack Elements Are :\n");
			DisplayStack(st);
			break;

		case 0:
			DeleteStack(st);
			printf("Programme Ended Successfully\n");
			break;

		default:
			printf("Invalid Choice\n");
			break;
		}


	}



	return 0;
}




