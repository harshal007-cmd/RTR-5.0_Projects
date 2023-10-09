#include<stdio.h>
#include<stdlib.h>


struct node 
{
	int data;
	struct node* next;
};

struct node* CreateStack(void);
int IsStackFull(struct node* st);
int IsStackEmpty(struct node* st);
void Push(struct node* st, int data);
int Pop(struct node* st);
int Top(struct node* st);
void DeleteStack(struct node* st);
void DisplayStack(struct node* st);