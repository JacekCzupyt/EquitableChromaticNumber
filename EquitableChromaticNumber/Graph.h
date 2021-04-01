#pragma once
#include<vector>
#include<set>

namespace ecnGraph {

	/// <summary>
	/// Represents a simple undirected graph
	/// </summary>
	class Graph {
	protected:
		std::vector<std::set<int>> Vertices;
	public:
		Graph(int n = 0/*Number of vertices*/);

		/// Returns the number of vertices in the graph
		int Size();

		/// <summary>
		/// Add vertices to the graph
		/// </summary>
		/// <param name="n">Number of vertices to add</param>
		/// <returns>The index of the last vertex of the new graph</returns>
		int AddVertex(int n = 1/*Number of vertices to add*/);

		/// <summary>
		/// Checks if there exists an edge between the two vertices
		/// </summary>
		/// <param name="a">Vertex a</param>
		/// <param name="b">Vertex b</param>
		/// <returns>Is "ab" an edge</returns>
		bool IsEdge(int a, int b);

		/// <summary>
		/// Adds an edge between two vertices 
		/// If it already exists, does nothing
		/// </summary>
		/// <param name="a">Vertex a</param>
		/// <param name="b">Vertex b</param>
		void AddEdge(int a, int b);

		/// <summary>
		/// Removes the edge between two vertices 
		/// If it does not exist, does nothing
		/// </summary>
		/// <param name="a">Vertex a</param>
		/// <param name="b">Vertex b</param>
		void RemoveEdge(int a, int b);

		/// Returns the maximum degree of the graph
		int Deg();

		/// Returns the degree of the the vetex k
		int Deg(int k);
	};
}
