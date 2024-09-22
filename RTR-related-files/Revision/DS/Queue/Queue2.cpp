#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int data;
	struct Node* next;
};

struct Node* front = NULL;
struct Node* rear  = NULL;

void enqueue(int iData)
{
	struct Node* temp;
	temp = (struct Node*)malloc(sizeof(struct Node));

	if (temp == NULL)
	{
		printf("\nQueue is full");
	}
	else
	{
		temp->data = iData;
		temp->next = NULL;

		if (front == NULL)
			front = rear = temp;
		else
		{
			rear->next = temp;
			rear = temp;
		}
	}
}

int dequeue()
{
	int iData = -1;
	struct Node* temp;

	if (front == NULL)
	{
		printf("\nQueue is empty");
	}
	else
	{
		iData = front->data;
		temp = front;
		front = front->next;
		free(temp);
	}
	return iData;
}

void display()
{
	struct Node* temp = front;
	printf("\nQueue Elemen\n");
	while (temp)
	{
		printf("---%d---", temp->data);
		temp = temp->next;
	}
	
}

int main()
{
	int iChoice, iNum;
	while (1)
	{
		printf("1. Enqueue\n");
		printf("2  Dequeue\n");
		printf("3. Display\n");
		printf("Enter your choice\n");
		scanf("%d", &iChoice);

		switch (iChoice)
		{
		case 1:
			printf("Enter an element you want to enqueue\n");
			scanf("%d", &iNum);
			enqueue(iNum);
			break;
		case 2:
			printf("Dequeued elements is : %d", dequeue());
			break;
		case 3:
			display();
			break;

		default:
			printf("Galat choice\n");
			break;
		}
	}
}







