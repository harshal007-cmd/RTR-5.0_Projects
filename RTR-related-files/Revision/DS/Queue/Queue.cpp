#include<stdio.h>
#include<stdlib.h>

struct Queue
{
	int front;
	int rear;
	int size;
	int* qArray;
};

void create(struct Queue* q, int iSize)
{
	q->size=iSize;
	q->front=q->rear-1;
	q->qArray=(int*)malloc(q->size*sizeof(int));
	if (!q->qArray)
	{
		printf("\nMemo allocation failed\n");
	}
}

void enqueue(struct Queue* q, int iData)
{
	if (q->rear == (q->size - 1))
	{
		printf("\nQueue is full");
	}
	else
	{
		q->rear++;
		q->qArray[q->rear] = iData;
	}
}

int dequeue(struct Queue* q)
{
	int iData = -1;
	if (q->front == q->rear)
	{
		printf("\nQueue is empty");
	}
	else
	{
		q->front++;
		iData = q->qArray[q->front];
	}
	return iData;
}

void display(struct Queue* q)
{
	int iLoop;
	printf("\nQueue elements\n");
	for (iLoop = q->front + 1; iLoop <= q->rear; iLoop++)
	{
		printf("---%d---", q->qArray[iLoop]);
	}
}

int main()
{
	struct Queue q;
	int iChoice, iNum;
	while (1)
	{
		printf("1. Create Queue\n");
		printf("2. Enqueue\n");
		printf("3  Dequeue\n");
		printf("4. Display\n");
		printf("Enter your choice\n");
		scanf("%d", &iChoice);

		switch (iChoice)
		{
		case 1:
			printf("Enter Size of Queue\n");
			scanf("%d", &iNum);
			create(&q, iNum);
			break;
		case 2:
			printf("Enter an element you want to enqueue\n");
			scanf("%d", &iNum);
			enqueue(&q, iNum);
			break;
		case 3:
			printf("Dequeued elements is : %d", dequeue(&q));
			break;
		case 4:
			display(&q);
			break;

		default:
			printf("Galat choice\n");
			break;
		}
	}
}







