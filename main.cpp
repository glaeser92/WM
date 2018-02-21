#include <iostream>
#include "UndirectedGraph.h"

int main() {

	UndirectedGraph g(8);
	g.addEdge(0, 1, 19);
	g.addEdge(0, 2, 8);
	g.addEdge(0, 3, 8);
	g.addEdge(0, 4, 18);
	g.addEdge(0, 5, 18);
	g.addEdge(0, 6, 25);
	g.addEdge(0, 7, 29);
	g.addEdge(1, 2, 0);
	g.addEdge(1, 3, 8);
	g.addEdge(1, 4, 10);
	g.addEdge(1, 5, 4);
	g.addEdge(1, 6, 15);
	g.addEdge(1, 7, 23);
	g.addEdge(2, 3, 4);
	g.addEdge(2, 4, 8);
	g.addEdge(2, 5, 2);
	g.addEdge(2, 6, 15);
	g.addEdge(2, 7, 18);
	g.addEdge(3, 4, 2);
	g.addEdge(3, 5, 10);
	g.addEdge(3, 6, 15);
	g.addEdge(3, 7, 16);
	g.addEdge(4, 5, 10);
	g.addEdge(4, 6, 22);
	g.addEdge(4, 7, 25);
	g.addEdge(5, 6, 19);
	g.addEdge(5, 7, 19);
	g.addEdge(6, 7, 37);

	g.minWeightMatching();

	return 0;
}