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
	
	void BitsColoringAlgorithm::TabooSearch::ExploreNeighborhood(int mt)
	{
		// TODO: replace GetColorCount with preexisting variable
		int colorCount = e.graph->GetColorCount();

		//N1
		int min_df1 = 1;
		int v1, c1;
		//For each vertex in graph
		for (int v = 0; v < e.graph->Size(); v++) {
			int vc = e.graph->Colors[v]; //current vertex color
			//If conflict
			if (evaluationMatrix[v][vc] > 0) {
				//For each avalible color
				for (int c = 0; c < colorCount; c++) {
					//If allowed by taboo list
					if (tabooList[v][c] < mt) {
						//delta f
						int df = evaluationMatrix[v][c] - evaluationMatrix[v][vc];
						//if best
						if (df < min_df1) {
							//replace best values
							min_df1 = df;
							v1 = v;
							c1 = c;
						}
					}
				}
			}
		}

		//N2

	}
}


