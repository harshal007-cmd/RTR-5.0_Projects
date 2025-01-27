#include<iostream>
using namespace std;

typedef struct Node
{
	int data;
	Node* next;
}node;

class List
{
private:
	node* head;
public:
	List() 
	{
		head = nullptr;
	}

	void insert(int value)
	{
		node* newNode = new node();
		newNode->data = value;
		newNode->next = nullptr;

		if (head == nullptr)
		{
			head = newNode;
		}
		else
		{
			node* temp = new node();
			temp = head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}

	void show()
	{
		node* temp = head;
		int count=0;
		while (temp != nullptr)
		{
			cout << temp->data << "->";
			temp = temp->next;
			count++;
		}
		cout << "\nNumber of elements in list: "<<count<<"\n\n";
	}

	void insertAt(int value, int pos)
	{
		node* newNode = new node();

		node* temp = head;
		int count = 0;
		while (temp != nullptr)
		{
			
			temp = temp->next;
			count++;
		}

		cout << "No of elements in list = " << count << "\n\n";
		if (pos < 0)
		{
			cout << "Cannot add at " << pos << " location\n";
			return;
		}
		if (pos == 1)
		{
			newNode->data = value;
			newNode->next = head;
			head = newNode;
			return;
		}
		if (pos > (count + 1))
		{
			cout << "Out of bounds\nThere are only " << count << " elements in linked list\n";
			return;
		}


		if (head == nullptr)
		{
			head = newNode;
			
		}
		else
		{
			node* current = new node();
			current = head;
			for (int i = 1; current != nullptr && i < pos - 1; ++i)
			{
				current = current->next;
			}
			newNode->data = value;
			newNode->next = current->next;
			current->next = newNode;

		}


	}

	void removeLast()
	{
		if (head == nullptr)
		{
			cout << "List is empty, nothing to remove\n";
			return;
		}

		if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
			cout << "last node removed, list is empty now!!\n\n";
		}

		node* current = new node();
		current = head;
		while (current->next->next != nullptr)
		{
			current = current->next;
		}
		delete current->next->next;
		current->next = nullptr;

	}

	void removeAt(int pos)
	{
		if (head == nullptr)
		{
			cout << "List is already empty\n\n";
			return;
		}

		if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
			cout << "List was contained only one element, list is empty now\n\n";
			return;
		}

		node* temp = new node();
		temp = head;
		for (int i = 1; temp != nullptr && i < pos - 1; ++i)
		{
			temp = temp->next;
		}
		node* nodeToDelete = temp->next;
		cout << "Deleted element is = " << nodeToDelete->data<<"\n\n";
		temp->next = temp->next->next;
		delete nodeToDelete;

	}

	~List()
	{
		node* temp = head;
		while (temp != nullptr) {
			node* next = temp->next;
			delete temp;
			temp = next;
		}
		cout << "Memory is free\n";

	}
};


int main()
{
	List list;
		
	int choice;

	cout << "Select operations to perform on LinkedList\n\n";
	while (1)
	{
		cout << "1. Add in linked list\n";
		cout << "2. Print linked list data\n";
		cout << "3. Add at location in list\n";
		cout << "4. Remove last element\n";
		cout << "5. Remove from location element\n";
		cout << "0. Exit\n\n";
		
		cin >> choice;

		switch (choice) {
		case 1:
			int x;
			cout << "Enter data to add in linked list = ";
			cin >> x;
			cout << "\n";
			list.insert(x);
			break;
		case 2:
			cout << "Data in linked list = ";
			list.show();
			break;
		case 3:
			int pos;
			cout << "Enter data to add\n";
			cin >> x;
			cout << "Enter position to add data\n";
			cin >> pos;
			list.insertAt(x, pos);
			break;
		case 4:
			list.removeLast();
			break;
		case 5:
			cout << "Enter poistion of element to remove\n";
			cin >> x;
			list.removeAt(x);
			break;
		case 0:
			exit(0);
			break;
		default:
			break;
		}
	}
	return 0;
}

