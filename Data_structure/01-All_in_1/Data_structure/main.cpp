#include<iostream>
#include"Queue.h"
using namespace std;

int main()
{
	cout << "All Data structure codes :\n" << endl;
	int choice = 0;

	while (1)
	{
		cout << "Select any one of following data strutrue to use\n" << endl;
		cout << "1. Queue\n";
		

		cout << "Enter your choice\n";
		cin >> choice;
			
		//All object initializations
		Queue* q = nullptr;
		///-------------------
		switch (choice)
		{
		case 1:
			cout << "Set length of Queue\n";
			int x;
			cin >> x;
			q = new Queue(x);
			q->main_Queue();
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Enter correct choice\n";
			break;
		}
	}

	return 0;
}