#include<iostream>
#include<list>
using namespace std;

class ListClass
{
private:
	list<int> myList;

public:
	void PushBack(int a)
	{
		myList.push_back(a);
	}

	void PushFront(int a)
	{
		myList.push_front(a);
	}

	void AtLocation(int value, int key)
	{
		auto it = myList.begin();
		advance(it, key);
		myList.insert(it, value);
	}
	
	void RemoveAt(int key)
	{
		auto it = myList.begin();
		advance(it, key);
		myList.erase(it);
	}

	void showList()
	{
		for (auto& element : myList)
		{
			cout << element << " ";
		}
	}
};


int main()
{
	ListClass lc;
	int i = 1;

	int num, pos;

	cout << endl;
	while (i)
	{
		int choice;
		cout << "Select one of following:\n";
		cout << "1. PushBack\n";
		cout << "2. PushFront\n";
		cout << "3. Add at Location\n";
		cout << "4. Remove at Location\n";
		cout << "5. Show List\n";
		cout << "0. For Exit\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Enter number to PushBack\n";
			cin >> num;
			lc.PushBack(num);
			break;
		case 2:
			cout << "Enter number to PushFront\n";
			cin >> num;
			lc.PushFront(num);

			break;
		case 3:
			cout << "Enter number and position to add in list\n";
			cout << "Enter number : " << endl;
			cin >> num;
			cout << "Enter Position : " << endl;
			cin >> pos;
			lc.AtLocation(num, pos);

			break;
		case 4:
			cout << "Enter postion to remove at location : " << endl;
			cin >> pos;
			lc.RemoveAt(pos);
			break;
		case 5:
			cout << "List element's are : " << endl;
			lc.showList();
			cout << endl;
			break;
		case 0:
			i = 0;
			break;

		default:
			cout << "Select correct option\n";
			break;
		}
	}
	cout << endl;
	return 0;
}










