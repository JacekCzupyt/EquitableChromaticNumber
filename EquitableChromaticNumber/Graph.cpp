#include "Graph.h"

namespace ecnGraph{
	
	/// O(n) time
	Graph::Graph(int n)
	{
		this->Vertices.resize(n);
	}

	/// O(1) time
	int Graph::Size() const
	{
		return Vertices.size();
	}

	/// O(n) time
	int Graph::AddVertex(int n)
	{
		Vertices.resize(Vertices.size() + n);
		return Vertices.size() - 1;
	}
	
	/// O(log deg(a)) time (deg(a) - degree of the a vertex)
	bool Graph::IsEdge(int a, int b) const
	{
		return Vertices[a].count(b);
	}

	/// O(log deg(a)+deg(b)) time
	void Graph::AddEdge(int a, int b)
	{
		Vertices[a].insert(b);
		Vertices[b].insert(a);
	}

	/// O(log deg(a)+deg(b)) time
	void Graph::RemoveEdge(int a, int b)
	{
		Vertices[a].erase(b);
		Vertices[b].erase(a);
	}

	/// O(|V|) time
	int Graph::Deg() const
	{
		int res = 0;
		for (int i = 0; i < Vertices.size();i++) {
			res = std::max(res, Deg(i));
		}
		return res;
	}

	/// O(1) time
	int Graph::Deg(int k) const
	{
		return Vertices[k].size();
	}


}

