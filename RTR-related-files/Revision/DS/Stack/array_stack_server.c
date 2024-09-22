
#include"stack_server.h"

struct stack* CreateStack(void)
{
	struct stack* temp;

	temp = (struct stack*)malloc(sizeof(struct stack));
	
	if (temp == NULL)
		return NULL;

	printf("Enter Size of The stack : ");
	scanf("%d", &temp->size);

	temp->arr = (int*)malloc(sizeof(int) * temp->size);
	temp->top = -1;
	
	return temp;
}


int IsStackFull(struct stack* st)
{
	if (st->top == st->size - 1)
		return 1;
	else
		return 0;
}


int IsStackEmpty(struct stack* st)
{
	if (st->top == -1)
		return 1;
	else
		return 0;

}

void Push(struct stack* st, int data)
{
	if (IsStackFull(st))
	{
		printf("Stack Overflow");
	}
	else
	{
		st->arr[++st->top] = data;
	}
}


int Pop(struct stack* st)
{
	if (IsStackEmpty(st))
	{
		printf("Stack Underflow");
		return INT_MIN;
	}
	else
	{
		return(st->arr[st->top--]);
	}
}

void DisplayStack(struct stack* st)
{
	if (IsStackEmpty(st))
		printf("Stack Is Empty");
	else
	{
		for (int i = st->top; i >= 0; i--)
		{
			printf("%d\n", st->arr[i]);
		}
	}
}
void DeleteStack(struct stack* st)
{	
	if (st != NULL)
	{
		if (st->arr != NULL)
			free(st->arr);

		free(st);
	}
}
