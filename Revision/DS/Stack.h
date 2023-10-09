#include<stdio.h>
#include<stdlib.h>


struct stack
{
	int* arr;
	int size;
	int top;

};

struct stack* CreateStack(void);
int IsStackFull(struct stack* st);
int IsStackEmpty(struct stack* st);
void Push(struct stack* st, int data);
int Pop(struct stack* st);
int Top(struct stack* st);
void DeleteStack(struct stack* st);
void DisplayStack(struct stack* st);