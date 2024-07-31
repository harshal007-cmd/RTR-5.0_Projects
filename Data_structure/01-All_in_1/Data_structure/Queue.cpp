#include"Queue.h"
#include<iostream>
#include<stdexcept>
using namespace std;

//Queue::Queue(int size) :arr(new int[size]), capacity(size), front(0), rear(-1), count(0) {}

void Queue::enqueue(int x)
{
	if (isFull())
	{
		cout<<"Queue is Full\n";
	}
	else
	{
		rear = (rear + 1) % capacity;
		arr[rear] = x;
		count++;

	}

}

int Queue::dqueue()
{
	if (isEmpty())
	{
		cout<<"Queue is Empty\n";
		return 0;
	}
	
		int data = arr[front];
		front = (front + 1) % capacity;
		count--;
		return data;
	
	
}

int Queue::peek()
{
	if (isEmpty())
	{
		cout<<"Queue is Empty\n";
	}
	else
	{
		return arr[front];
	}

}

int Queue::qsize()
{
	return count;
}

bool Queue::isEmpty()
{
	return count == 0;
}

bool Queue::isFull()
{
	return count == capacity;
}

void Queue::showAll()
{
	cout << "Data in Queue = ";
	for (int i = 0; i < count; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << "\n"<<endl;
}

void Queue::main_Queue()
{
	int choice;
	std::cout << "Select options to perform on Queue\n\n";
	int x, y, z, p;
	while (1)
	{

		cout << "1. Add in Queue\n";
		cout << "2. Delete from queue\n";
		cout << "3. Check size of queue\n";
		cout << "4. Check first element\n";
		cout << "5. Check all Data in queue\n";
		cout << "0. Exit\n";
		cout << "\n";
		cout << "Enter your choice = ";
		cin >> choice;
		cout << "\n";
		switch (choice)
		{
		case 1:
			x;
			cout << "Enter number to enter in queue\n";
			cin >> x;
			enqueue(x);
			break;
		case 2:
			y = dqueue();
			cout << "Deleted data is = " << y<<"\n";
			break;
		case 3:
			z = qsize();
			cout << "Size of Queue is = " << z<<"\n";
			break;
		case 4:
			p = peek();
			cout << "Element at front of queue is = " << p<<"\n";
			break;
		case 5:
			showAll();
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Enter correct option\n";
			break;
		}
	}
}
