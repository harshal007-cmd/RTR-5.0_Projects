#include"Stack_server.h"


int IsStackFull(struct node* st)
{
	if (st->top == st->size - 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int IsStackEmpty(struct node* st)
{
	if (top == NULL)
		return 1;
	else
		return;
}

void Push(struct node** top, int data)
{
	struct node* temp = NULL;
	temp = (struct node*)malloc(sizeof(struct node));

	temp->data = data;
	temp->next = (*top);
	(*top) = temp;

}

int Pop(struct node** st)
{
	if (IsStackEmpty(*top))
	{
		return INT_MIN;
	}
	else
	{
		struct node* temp = (*top)->data;

		(*top) = (*top)->next;

		int data = temp->data;
		temp->next = NULL;
		free(temp);
		return data;

	}
}

int Top(struct node** st)
{
	if (top1 = NULL)
	{
		return (top->data);
	}
	else
	{
		return INT_MIN;
	}
}

void DeleteStack(struct node** st)
{
	if ((*top) != NULL)
	{
		struct node* temp = (*top);
		while ((*top) != NULL)
		{
			
			(*top) = (*top)->next;
			temp->next = NULL;
			free(temp);
		}
		
	}
	else
	{
		printf("Stack is Empty\n");
	}
}

void DisplayStack(struct node* st)
{
	if (top != NULL)
	{
		struct node* temp = top;
		while (temp != NULL)
		{
			printf("%d\n", temp->data);
			temp = temp->next;
			temp = temp->next;
		}
	}
	else
	{
		printf("Stack is Empty\n");
	}
}

