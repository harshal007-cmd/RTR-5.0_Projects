#include"stack_server.h"


void Push(struct node** top, int data)
{

	struct node* temp = (struct node*)malloc(sizeof(struct node));

	if (temp == NULL)
		return;
	temp->data = data;
	temp->next = (*top);
	(*top) = temp;

}
int IsStackEmpty(struct node* top)
{
	if (top == NULL)
		return 1;
	else
		return 0;
}

int Pop(struct node** top)
{
	if (IsStackEmpty(*top))
	{
		printf("Stack is Empty");
		return INT_MIN;
	
	}
	else
	{
		int data = (*top)->data;

		struct node* temp = (*top);
		(*top) = (*top)->next;

		temp->next = NULL;
		free(temp);
		temp = NULL;

		return data;
	}
}


int Top(struct node* top)
{
	if (IsStackEmpty(top))
		return INT_MIN;
	else
		return (top->data);
}

void DisplayStack(struct node* top)
{
	struct node* temp = top;

	if (temp == NULL)
		printf("stack Is Empty");
	else
	{
		printf("Stack Elements Are :\n");

		while (temp != NULL)
		{
			printf("%d\n", temp->data);
			temp = temp->next;
		}
	}

}

void DeleteStack(struct node** top)
{
	struct node* temp;
	while ((*top != NULL))
	{
		temp = (*top);
		(*top) = (*top)->next;

		temp->next = NULL;
		free(temp);
		temp = NULL;
	}

}
