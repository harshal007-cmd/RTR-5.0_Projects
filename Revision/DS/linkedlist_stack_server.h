#pragma once
#include<stdio.h>
#include<stdlib.h>




struct node
{
	int data;
	struct node* next;
};


void Push(struct node** top, int data);
int IsStackEmpty(struct node* top);
int Pop(struct node** top);
int Top(struct node* top);
void DisplayStack(struct node* top);
void DeleteStack(struct node** top);
