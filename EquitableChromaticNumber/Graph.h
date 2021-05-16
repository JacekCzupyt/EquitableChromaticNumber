#pragma once
#include<vector>
#include<set>

namespace ecnGraph {

	/// <summary>
	/// Represents a simple undirected graph
	/// </summary>
	class Graph {
	
		
	public:

		std::vector<std::set<int>> Vertices;

		Graph(int n = 0/*Number of vertices*/);

		/// Returns the number of vertices in the graph
		int Size() const;

		/// <summary>
		/// Returns the set of neighbouring verticies of the vertex a
		/// </summary>
		/// <param name="a">Vertex a</param>
		/// <returns>Set of verticies b, such that "ab" is an edge in the graph</returns>
		const std::set<int>& GetNeighbours(int a) const;

		/// <summary>
		/// Add vertices to the graph
		/// </summary>
		/// <param name="n">Number of vertices to add</param>
		/// <returns>The index of the last vertex of the new graph</returns>
		virtual int AddVertex(int n = 1/*Number of vertices to add*/);

		/// <summary>
		/// Checks if there exists an edge between the two vertices
		/// </summary>
		/// <param name="a">Vertex a</param>
		/// <param name="b">Vertex b</param>
		/// <returns>Is "ab" an edge</returns>
		bool IsEdge(int a, int b) const;

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
		int Deg() const;

		/// Returns the degree of the the vetex k
		int Deg(int k) const;
	};
}
