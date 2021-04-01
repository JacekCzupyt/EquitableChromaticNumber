#pragma once
#include "Graph.h"

namespace ecnGraph {

	/// <summary>
	/// Represents a simple colored undirected graph
	/// </summary>
	class ColoredGraph :
		public Graph
	{
	public:
		/// Colors are consecutive intigers starting from 0, -1 means no color is assigned to this vertex
		std::vector<int> Colors;

		ColoredGraph(int n/*Number of vertices*/);

		/// <summary>
		/// Add vertices to the graph
		/// </summary>
		/// <param name="n">Number of vertices to add</param>
		/// <returns>The index of the last vertex of the new graph</returns>
		int AddVertex(int n) override;

		/// Returns the number of different colors used, does not count uncolored vertices (color -1)
		int GetColorCount() const;

		/// Checks if every vertex has a color
		bool IsColoredFully() const;

		/// Checks if the coloring is proper
		bool IsColoredProperly() const;
		
		/// <summary>
		/// Checks if the coloring is equitable
		/// Does NOT check if coloring is proper
		/// </summary>
		bool IsColoredEquitably() const;
	};

}


