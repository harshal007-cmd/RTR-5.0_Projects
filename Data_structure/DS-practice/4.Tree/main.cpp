#include<iostream>
#include<chrono>
using namespace std;

struct Node
{
	int data;
	Node* left;
	Node* right;

	Node(int value)
	{
		data = value;
		left = nullptr;
		right = nullptr;
	}
};


class Tree
{
private:
	Node* root;

	Node* insertNode(Node* node, int value)
	{
		if (node == nullptr)
		{
			return new Node(value);
		}

		if (value < node->data)
		{
			node->left = insertNode(node->left, value);
		}
		else
		{
			node->right = insertNode(node->right, value);
		}
		return node;
	}

	void inorderShow(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}

		inorderShow(node->left);
		cout << node->data << " ";
		inorderShow(node->right);
	}

	void preOrderShow(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}

		cout << node->data << " ";
		preOrderShow(node->left);
		preOrderShow(node->right);
	}

	void postOrderShow(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}

		postOrderShow(node->left);
		postOrderShow(node->right);
		cout << node->data << " ";

	}

public:
	Tree()
	{
		root = nullptr;
	}

	void insert(int value)
	{
		root = insertNode(root, value);
	}

	

	void inorder()
	{
		cout << "In order tree: ";
		inorderShow(root);
		cout << "\n";
	}

	void preOrder()
	{
		cout << "Pre order tree: ";
		preOrderShow(root);
		cout << "\n";
	}

	void postOrder()
	{
		cout << "Post order tree: ";
		postOrderShow(root);
		cout << "\n";
	}

	void freeMemo(Node* node)
	{
		
		if (node != nullptr)
		{
			freeMemo(node->left);
			freeMemo(node->right);
			delete node;
		}
	}

	~Tree()
	{
		freeMemo(root);
		cout << "In freeMemo(), memory released\n\n";
	}
};

int main()
{
	Tree tree;

	int choice;
	chrono::high_resolution_clock::time_point start, end;
	while (1)
	{

		cout << "Enter option number from following\n\n";
		cout << "1. Insert in tree.\n";
		cout << "2. Inorder.\n";
		cout << "3. Preorder.\n";
		cout << "4. Postorder.\n";
		cout << "0. Exit.\n\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			int x;
			cout << "\nEnter node data to enter\n";
			cin >> x;
			tree.insert(x);
			break;
		case 2:
			start = chrono::high_resolution_clock::now();

			tree.inorder();

			end = chrono::high_resolution_clock::now();
			chrono::duration<double, milli> duration = end - start;
			cout << "\nInorder traversal time = " << duration.count() << "ms\n";
			break;
		case 3:
			start = chrono::high_resolution_clock::now();

			tree.preOrder();

			end = chrono::high_resolution_clock::now();
			duration = end - start;
			cout << "\nPreorder traveral time = " << duration.count() << "ms\n";
			
			break;
		case 4:
			start = chrono::high_resolution_clock::now();
			
			tree.postOrder();
			
			end = chrono::high_resolution_clock::now();
			duration = end - start;
			cout << "\nPost order traveral time = " << duration.count() << "ms\n";
			
			break;
		case 0:
			cout << "\nExiting from Tree program\n\n";
			break;
		default:
			break;
		}

		if (choice == 0)
			break;
	}
	cout << "\n\nMain Program ends here\n\n";

	return 0;
}
