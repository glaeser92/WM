#pragma once

#include <list>
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

class UndirectedGraph
{
public:
	explicit UndirectedGraph(int V);
	~UndirectedGraph();
	void addEdge(int u, int v, double weight);
	void printMatching();
	void printGraph();
	void minWeightMatching();
private:
	int V;
	double** C;
	int* match;
	int* label;
	int* base;
	bool* blossom;

	int lca(const int* match, const int* base, int* p, int a, int b);
	void markPath(const int* match, const int* base, bool* blossom, int* p,
		int v, int b, int children);
	int findPath(list<int>* adj, int* match, int* p, int root);
	int sizeMatching();
	void maxMatching(list<int>* adj);
};