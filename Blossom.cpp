#include "Blossom.h"

Blossom::Blossom(int stem)
{
	this->stem = stem;
	this->nodes = new set<int>;
}

void Blossom::addNode(int n) const
{
	this->nodes->insert(n);
}

void Blossom::updateStem(int* match)
{
	for (int i : *nodes)
	{
		//if matching partner of i is not in blossom
		if(nodes->find(match[i]) == nodes->end())
		{
			//i is new stem
			stem = i;
		}
	}
}

void Blossom::print() const
{
	for (int i : *nodes)
	{
		cout << i << " ";
	}
	cout << endl;
}

int Blossom::getStem() const
{
	return this->stem;
}
