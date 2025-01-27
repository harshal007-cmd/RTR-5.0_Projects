#include"Graph.h"

Graph::~Graph()
{
	for (int i = 0; i < vertex; ++i)
	{
		delete[]Adj[i];
	}
	delete[]Adj;
}

void Graph::initGraph()
{
	cout << "Enter vertices for Graph: \n";
	int graphVertices;
	cin >> graphVertices;
	vertex = graphVertices;
	Adj = new int* [vertex];
	for (int i = 0; i < vertex; ++i)
	{
		Adj[i] = new int[vertex];
		for (int j = 0; j < vertex; ++j)
		{
			Adj[i][j] = 0;
		}
	}
	cout << "Initialization of Graph is done.\n";
}

void Graph::addEdge(int u, int v)
{
	if (u < 0 || u >= vertex || v < 0 || v >= vertex)
	{
		cout << "Error invalid edge (" << u << ", " << v << ")" << endl;
		return;
	}
	Adj[u][v] = 1;
	Adj[v][u] = 1;
	edges++;
}

void Graph::displayGraph()
{
	for (int i = 0; i < Graph::vertex; ++i)
	{
		for (int j = 0; j < Graph::vertex; ++j)
		{
			cout << Adj[i][j] << " ";
		}
		cout << endl;
	}
}

void Graph::mainGraph()
{
	int choice;
	initGraph();
	cout << "Select Graph operations:\n";
	while (1)
	{
		cout << "1. Add edge.\n";
		cout << "2. Display Graph.\n";
		cout << "0. Exit.\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Enter vertex and edge:\n";
			int u, v;
			cout << "Enter vertex:\n";
			cin >> u;
			cout << "Enter edge:\n";
			cin >> v;
			addEdge(u, v);
			break;
		case 2:
			displayGraph();
			break;

		case 0:
			exit(0);
			break;
		default:
			break;
		}
	}
}