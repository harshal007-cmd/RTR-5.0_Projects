#include"stack_server.h"

int main(void)
{
	int choice = 1;
	struct node* top = NULL;
	int data;

	while (choice != '0')
	{
		printf("\n\n1.Push\n2.Pop\n3.Is Empty\n4.Top Element\n5.Display\n0.End\n");
		printf("Enter Your Choice : ");
		printf("\n");
		choice = getch();

		switch (choice)
		{
		case '1':
			printf("Enter Data To be Pushed : ");
			scanf("%d", &data);
			Push(&top, data);

			DisplayStack(top);
			break;

		case '2':
			data = Pop(&top);
			if (data != INT_MIN)
			{
				printf("Removed Element from the stack Is : %d\n", data);
				DisplayStack(top);
			}
			break;

		case '3':
			if (IsStackEmpty(top))
				printf("Stack Is Empty\n");
			else
				printf("stack Is Not Empty\n");
			break;

		case '4':
			data = Top(top);
			if (data != INT_MIN)
				printf("Top Data Element of Stack Is : %d\n", data);
			else
				printf("Stack Is Empty\n");
			break;

		case '5':
			DisplayStack(top);
			break;

		case '0':
			DeleteStack(&top);
			printf("Programme Ended Successfully\n");
			break;

		default:
			printf("Invalid Choice\n");
			break;
		}


	}



	return 0;
}




