#include<iostream>
using namespace std;

typedef struct Node
{
	int value;
	Node* next;
}node;

typedef struct Graph
{
	int vertex;
	node** adj;
}graph;

node* createNode(int val)
{
	node* newNode = (node*)malloc(sizeof(node));

	newNode->value = val;
	newNode->next = NULL;
	return newNode;
}

graph* createGraph(int nodes)
{
	graph* graphNode = (graph*)malloc(sizeof(graph));
	graphNode->vertex = nodes;

	//array of nodes
	graphNode->adj = (node**)malloc(nodes * sizeof(node*));

	for (int i = 0; i < graphNode->vertex; ++i)
	{
		graphNode->adj[i] = NULL;
	}

	return graphNode;
}

void addEdge(graph* graphNode, int src, int dest)
{
	//dest to src edge
	node* newNode = createNode(dest);

	newNode->next = graphNode->adj[dest];
	graphNode->adj[src] = newNode;

	//src to dest edge
	newNode = createNode(src);
	newNode->next = graphNode->adj[src];
	graphNode->adj[dest] = newNode;
	
}

void printGraph(graph* graphNode) {
	for (int v = 0; v < graphNode->vertex; v++) {
		node* temp = graphNode->adj[v];
		printf("Vertex %d: ", v);
		while (temp) {
			printf("%d -> ", temp->value);
			temp = temp->next;
		}
		printf("NULL\n");
	}
}

int main()
{
	int vertices = 5;

	graph* graphNode = createGraph(vertices);

	// Add edges to the graph
	addEdge(graphNode, 0, 1);
	addEdge(graphNode, 0, 4);
	addEdge(graphNode, 1, 2);
	addEdge(graphNode, 1, 3);
	addEdge(graphNode, 1, 4);
	addEdge(graphNode, 2, 3);
	addEdge(graphNode, 3, 4);

	// Print the graph
	printGraph(graphNode);


	return 0;
}



