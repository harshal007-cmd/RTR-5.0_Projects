#include"Stack.h"

struct stack* CreateStack(void)
{
	struct stack* temp = NULL;
	printf("Enter number of Stack Element : ");
	scanf("%d", &(temp->size));
	temp->top = -1;

	temp->arr = (int*)malloc(sizeof(int) * temp->size);
	
	return temp;
}

int IsStackFull(struct stack* st)
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

int IsStackEmpty(struct stack* st)
{
	if (st->top == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Push(struct stack* st, int data)
{
	if (IsStackFull(st))
	{
		printf("Stack Overflow\n");
	}
	else
	{
		st->top++;
		st->arr[st->top] = data;
	}
	
}

int Pop(struct stack* st)
{
	if (IsStackEmpty(st))
	{
		printf("Stack Underflow\n");
		return INT_MIN;
	}
	else
	{
		int data = Top(st);
		st->top--;

		return data;
	}
}

int Top(struct stack* st)
{
	if (IsStackEmpty(st))
	{
		printf("Stack is Empty\n");
		return INT_MIN;
	}
	else
	{
		return st->arr[st->top];
	}
}

void DeleteStack(struct stack* st)
{
	if (st!=NULL)
	{
		free(st->arr);
		free(st);
	}
}

void DisplayStack(struct stack* st)
{
	if (IsStackEmpty(st))
	{
		printf("Stack is empty\n");
	}
	else
	{
		printf("Stack Elements Are: \n");

		for (int i = st->top;i >= 0;i--)
		{
			printf("%d\n", st->arr[i]);
		}
	}
}

