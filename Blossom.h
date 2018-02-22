#pragma once

#include <iostream>
#include <set>

using namespace std;

class Blossom
{
public:
	explicit Blossom(int stem);
	void addNode(int n) const;
	void updateStem(int* match);
	void print() const;
	int getStem() const;

private:
	int stem;
	set<int> * nodes;
};
