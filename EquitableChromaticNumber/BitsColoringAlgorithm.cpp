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

	std::vector<std::vector<int>> BitsColoringAlgorithm::ConstructEvaluationMatrix()
	{
		// TODO: replace GetColorCount with preexisting variable
		auto matrix = std::vector<std::vector<int>>(graph->Size(), std::vector<int>(graph->GetColorCount(), 0));
		for (int i = 0; i < graph->Size(); i++) {
			for (int j : graph->GetNeighbours(i)) {
				matrix[i][j]++;
			}
		}
		return matrix;
	}
}


