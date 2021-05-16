#pragma once
#include "Graph.h"
#include<vector>
#include<set>
#include "ColoredGraph.h"
#include "AbstractColoringAlgorithm.h"

namespace ecnGraph {

	class GreedyAlgorithm :
		public AbstractColoringAlgorithm
	{
	public:
		int Color(ColoredGraph& Graph);
	};
}



