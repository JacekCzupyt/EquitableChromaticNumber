#include "BitsColoringAlgorithm.h"

namespace ecnGraph {
	BitsColoringAlgorithm::BitsColoringAlgorithm(double _duration)
	{
		duration = _duration;
	}

	int ecnGraph::BitsColoringAlgorithm::Color(ColoredGraph& _graph)
	{
		return 0;
	}

	BitsColoringAlgorithm::TabooSearch::TabooSearch(BitsColoringAlgorithm& _e) : e(_e) {}

	std::vector<std::vector<int>> BitsColoringAlgorithm::TabooSearch::ConstructEvaluationMatrix()
	{
		// TODO: replace GetColorCount with preexisting variable
		auto matrix = std::vector<std::vector<int>>(e.graph->Size(), std::vector<int>(e.graph->GetColorCount(), 0));
		for (int i = 0; i < e.graph->Size(); i++) {
			for (int j : e.graph->GetNeighbours(i)) {
				matrix[i][j]++;
			}
		}
		return matrix;
	}

	std::vector<std::vector<int>> BitsColoringAlgorithm::TabooSearch::InitializeTabooList()
	{
		// TODO: replace GetColorCount with preexisting variable
		return std::vector<std::vector<int>>(e.graph->Size(), std::vector<int>(e.graph->GetColorCount(), INT_MIN));
	}
	
	void BitsColoringAlgorithm::TabooSearch::ExploreNeighborhood()
	{

	}
}


