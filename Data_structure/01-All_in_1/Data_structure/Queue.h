#pragma once
#include<iostream>

class Queue
{
private:
	int* arr;
	int capacity, size;
	int front, rear, count;

public:
	Queue(int size) :arr(new int[size]), capacity(size), front(0), rear(-1), count(0) {};
	void enqueue(int x);
	int dqueue();
	int peek();
	int qsize();
	bool isEmpty();
	bool isFull();
	void showAll();
	void main_Queue();
	~Queue()
	{
		delete[]arr;
	}
};

