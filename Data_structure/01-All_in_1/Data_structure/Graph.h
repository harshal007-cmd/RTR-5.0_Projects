#pragma once
#include<iostream>
using namespace std;

class Graph
{
private:
	int vertex, edges;
	int** Adj;
public:
	Graph() : vertex(0), edges(0), Adj(nullptr) {}
	
	void initGraph();
	void addEdge(int u, int v);
	void displayGraph();
	void mainGraph();
	~Graph();
	
};