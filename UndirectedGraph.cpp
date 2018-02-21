#include "UndirectedGraph.h"


UndirectedGraph::UndirectedGraph(int V) {
	this->V = V;

	C = new double *[V];
	match = new int[V];
	base = new int[V];
	blossom = new bool[V];
	label = new int[V];

	for (int i = 0; i < V; i++) {
		C[i] = new double[V];
		match[i] = -1;
		blossom[i] = false;
		base[i] = i;
	}

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			C[i][j] = 0;
		}
	}
}

UndirectedGraph::~UndirectedGraph() {
}

void UndirectedGraph::addEdge(int v, int u, double weight) {
	C[u][v] = C[v][u] = weight;
}

void UndirectedGraph::printMatching() {
	for (int i = 0; i < V; i++) {
		if (match[i] != -1) {
			cout << i << " -- " << match[i] << endl;
		}
	}
}

void UndirectedGraph::printGraph() {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			cout << C[i][j] << " ";
		}
		cout << endl;
	}
}

int UndirectedGraph::lca(const int *match, const int *base, int *p, int a, int b) {
	auto *used = new bool[V];
	for (int i = 0; i < V; i++) {
		used[i] = false;
	}
	while (true) {
		a = base[a];
		used[a] = true;
		if (match[a] == -1)
			break;
		a = p[match[a]];
	}
	while (true) {
		b = base[b];
		if (used[b])
			return b;
		b = p[match[b]];
	}
}

void UndirectedGraph::markPath(const int *match, const int *base, bool *blossom, int *p, int v, int b, int children) {
	//while we have not arrived at the stem
	while (base[v] != b) {
		blossom[base[v]] = blossom[base[match[v]]] = true;
		//set predecessor
		p[v] = children;
		children = match[v];

		v = p[match[v]];
	}
}

int UndirectedGraph::findPath(list<int>* adj, int* match, int* p, int root)
{
	auto * used = new bool[V];
	for (int i = 0; i < V; i++)
	{
		p[i] = -1;
		used[i] = false;
	}
	used[root] = true;

	//index of head in queue
	int qh = 0;
	//index of tail in queue
	int qt = 0;
	//queue array
	auto * q = new int[V];
	//add root to queue
	q[qt++] = root;

	while (qh < qt)
	{
		//get head element of queue
		int v = q[qh++];

		label[v] = 0;

		for (int& to : adj[v])
		{
			//if v and to are in the same blossom or
			if (base[v] == base[to] || match[v] == to)
				continue;
			//if blossom detected
			if (to == root || (match[to] != -1 && p[match[to]] != -1))
			{
				//find blossom base
				int curbase = lca(match, base, p, v, to);
				
				//maybe wrong
				label[curbase] = 1;

				//mark nodes in blossom
				for (int i = 0; i < V; i++) {
					blossom[i] = false;
				}
				blossom[curbase] = true;
				markPath(match, base, blossom, p, v, curbase, to);
				markPath(match, base, blossom, p, to, curbase, v);
				for (int i = 0; i < V; i++)
					//if i is in blossom
					if (blossom[base[i]])
					{
						//set blossom base
						base[i] = curbase;

						//add i to queue if not used
						if (!used[i])
						{
							used[i] = true;
							q[qt++] = i;
						}
					}
			}
			//if to is not in the tree
			else if (p[to] == -1)
			{
				label[to] = 1;

				//add to to tree with root v
				p[to] = v;

				//if to is a free vertex
				if (match[to] == -1)
					return to;

				int matchTo = match[to];
				used[matchTo] = true;
				q[qt++] = matchTo;
			}
		}
	}
	return -1;
}

void UndirectedGraph::maxMatching(list<int>* adj) {
	auto *p = new int[V];
	//for each vertex
	for (int i = 0; i < V; i++)
		if (match[i] == -1) {
			//if vertex is free look for augmenting path
			int v = findPath(adj, match, p, i);
			//augment along path
			while (v != -1) {
				int pv = p[v];
				int ppv = match[pv];
				match[v] = pv;
				match[pv] = v;
				v = ppv;
			}
		}

	for (int i = 0; i < V; i++) {
		label[i] = -1;
	}

	for (int i = 0; i < V; i++)
		if (match[i] == -1) {
			//if vertex is free look for augmenting path
			findPath(adj, match, p, i);
		}

	//set labels to blossom root
	for (int i = 0; i < V; i++)
	{
		label[i] = label[base[i]];
	}
}

int UndirectedGraph::sizeMatching() {
	int size = 0;

	for (int i = 0; i < V; i++) {
		if (match[i] != -1) {
			size++;
		}
	}

	return size / 2;
}

void UndirectedGraph::minWeightMatching() {

	auto * a = new double[V];
	auto * y = new double[V];

	for (int i = 0; i < V; i++) {
		y[i] = 0;
		//initialize vertex weights alpha
		double min = numeric_limits<double>::max();
		for (int j = 0; j < V; j++) {
			if (C[i][j] < min && i != j)
				min = C[i][j];
		}
		a[i] = min / 2;
	}

	while (sizeMatching() < V / 2) {
		//contruct graph consisting of admissable edges
		auto * adj = new list<int>[V];

		//add new edges to admissable graph
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (i != j) {
					//TODO: shrink blossom with negativ y value
					if (base[i] == base[j] && C[i][j] == a[i] + a[j] + y[base[i]]) {
						adj[i].push_back(j);
						adj[j].push_back(i);
					}
					else if (C[i][j] == a[i] + a[j]) {
						adj[i].push_back(j);
						adj[j].push_back(i);
					}
				}
			}
		}

		for (int i = 0; i < V; i++)
		{
			base[i] = i;
			blossom[i] = false;
		}

		//calculate max matching in admissable graph
		maxMatching(adj);

		//calculate delta values
		double delta1 = numeric_limits<double>::max();
		double delta2 = numeric_limits<double>::max();
		double delta3 = numeric_limits<double>::max();

		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (label[i] == 0 && label[j] == 0 && base[i] != base[j] && (C[i][j] - a[i] - a[j]) / 2 < delta1)
					delta1 = (C[i][j] - a[i] - a[j]) / 2;
				if (label[i] == 0 && label[j] == -1 && C[i][j] - a[i] - a[j] < delta2)
					delta2 = C[i][j] - a[i] - a[j];
			}
			if (blossom[i] && label[base[i]] == 1 && -(y[base[i]] / 2) < delta3) {
				delta3 = -(y[base[i]] / 2);
			}
		}

		//get minimum of deltas
		double Delta = min({ delta1, delta2, delta3 });

		auto * yUpdated = new bool[V];
		for (int i = 0; i < V; i++)
		{
			yUpdated[i] = false;
		}

		//update vertex weights
		for (int i = 0; i < V; i++) {
			if (label[i] == 0)
				a[i] = a[i] + Delta;
			if (label[i] == 1)
				a[i] = a[i] - Delta;
			if (blossom[i] && label[base[i]] == 0 && !yUpdated[base[i]])
			{
				y[base[i]] = y[base[i]] - (2 * Delta);
				yUpdated[base[i]] = true;
			}
				
			if (blossom[i] && label[base[i]] == 1 && !yUpdated[base[i]])
			{
				y[base[i]] = y[base[i]] + (2 * Delta);
				yUpdated[base[i]] = true;
			}
				
		}

		//TODO: recover blossoms with y[i] == 0

		delete[](adj);

	}
}