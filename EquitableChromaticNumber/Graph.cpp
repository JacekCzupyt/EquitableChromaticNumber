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

	int Graph::AddVertex(int n)
	{
		Vertices.resize(Vertices.size() + n);
		return Vertices.size() - 1;
	}
	
	bool Graph::IsEdge(int a, int b)
	{
		return Vertices[a].count(b);
	}

	void Graph::AddEdge(int a, int b)
	{
		Vertices[a].insert(b);
		Vertices[b].insert(a);
	}

	void Graph::RemoveEdge(int a, int b)
	{
		Vertices[a].erase(b);
		Vertices[b].erase(a);
	}

	int Graph::Deg()
	{
		int res = 0;
		for (int i = 0; i < Vertices.size();i++) {
			res = std::max(res, Deg(i));
		}
		return res;
	}

	int Graph::Deg(int k)
	{
		return Vertices[k].size();
	}


}

