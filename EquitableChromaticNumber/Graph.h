#pragma once
#include<vector>
#include<set>

namespace ecnGraph {
	using namespace std;

	class Graph {
	protected:
		vector<set<int>> Vertices;
	public:
		Graph(int n = 0);
		int Size();
		int AddVertex(int n = 0);

		bool IsEdge(int a, int b);
		void AddEdge(int a, int b);
		void RemoveEdge(int a, int b);

		int Deg();
		int Deg(int k);
	};
}
