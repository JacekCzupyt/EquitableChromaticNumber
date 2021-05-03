#pragma once
#include "ColoredGraph.h"

namespace ecnGraph {
	/// <summary>
	/// Interface representing a equitable coloring alogrithm
	/// </summary>
	class AbstractColoringAlgorithm {
	public:
		/// <summary>
		/// Estimates the equitable chromatic number of the provied graph and colors it appropietly
		/// </summary>
		/// <param name="Graph">Graph to be colored</param>
		/// <returns>Estimated equitable chromatic nubmer</returns>
		virtual int Color(ColoredGraph& Graph) = 0;
	};
}