#include "Graph.h"
namespace ecnGraph{

	Graph::Graph(int n)
	{
		this->Vertices.resize(n);
	}

	int Graph::Size()
	{
		return Vertices.size();
	}
}

