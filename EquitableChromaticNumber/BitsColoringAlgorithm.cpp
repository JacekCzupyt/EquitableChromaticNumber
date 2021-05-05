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

	std::vector<int> BitsColoringAlgorithm::TabooSearch::InitializeColorHistogram()
	{
		// TODO: replace GetColorCount with preexisting variable
		auto hist = std::vector<int>(e.graph->GetColorCount(), 0);
		for (int i = 0; i < e.graph->Size(); i++) {
			hist[e.graph->Colors[i]]++;
		}
		return hist;
	}
	
	void BitsColoringAlgorithm::TabooSearch::ExploreNeighborhood(int mt)
	{
		// TODO: replace GetColorCount with preexisting variable
		int colorCount = e.graph->GetColorCount();
		int lowIndex = e.graph->Size() / colorCount;
		int highIndex = lowIndex + (e.graph->Size() % colorCount == 0);

		//N1
		int min_df1 = 0;
		int v1 = 0, c1 = e.graph->Colors[0];

		//If n1 changes are possible
		if (lowIndex < highIndex) {
			//For each vertex in graph
			for (int v = 0; v < e.graph->Size(); v++) {
				int vc = e.graph->Colors[v]; //current vertex color
				//If conflict and high index (can be changed)
				if (evaluationMatrix[v][vc] > 0 && colorHistogram[vc] == highIndex) {
					//For each avalible color
					for (int c = 0; c < colorCount; c++) {
						//If allowed by taboo list and low index (can be increased
						if (tabooList[v][c] < mt && colorHistogram[c] == lowIndex) {
							//delta f
							int df = evaluationMatrix[v][c] - evaluationMatrix[v][vc];
							//if best
							if (df <= min_df1) {
								//replace best values
								min_df1 = df;
								v1 = v;
								c1 = c;
							}
						}
					}
				}
			}
		}
		

		//N2
		int min_df2 = 0;
		int v2 = 0, v3 = 0;

		//For each vertex in graph
		for (int v = 0; v < e.graph->Size(); v++) {
			int vc = e.graph->Colors[v]; //current vertex color
			//If conflict
			if (evaluationMatrix[v][vc] > 0) {
				//For each other vertex in graph
				for (int u = 0; u < e.graph->Size(); u++) {
					int uc = e.graph->Colors[u]; //current vertex color
					//If allowed by taboo list and not same vertex
					if (v != u && tabooList[v][uc] < mt && tabooList[u][vc] < mt) {
						//delta f
						int df = (evaluationMatrix[v][uc] - evaluationMatrix[v][vc])+(evaluationMatrix[u][vc] - evaluationMatrix[u][uc]) - 2 * (e.graph->IsEdge(v, u));
						//if best
						if (df <= min_df1) {
							//replace best values
							min_df2 = df;
							v2 = v;
							v3 = u;
						}
					}
				}
			}
		}
	}
}


