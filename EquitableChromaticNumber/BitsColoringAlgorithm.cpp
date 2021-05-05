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

	int BitsColoringAlgorithm::TabooSearch::EvaluationFunction(const std::vector<int>& colors)
	{
		int res = 0;
		for (int i = 0; i < e.graph->Size(); i++) {
			res += evaluationMatrix[i][colors[i]];
		}
		return res/2;
	}

	int BitsColoringAlgorithm::TabooSearch::EvaluationFunction()
	{
		return EvaluationFunction(e.graph->Colors);
	}
	
	BitsColoringAlgorithm::TabooSearch::move BitsColoringAlgorithm::TabooSearch::ExploreNeighborhood(int mt)
	{
		// TODO: replace GetColorCount with preexisting variable
		int colorCount = e.graph->GetColorCount();
		int lowIndex = e.graph->Size() / colorCount;
		int highIndex = lowIndex + (e.graph->Size() % colorCount == 0);


		int min_df = 0;
		int v1 = 0, c1 = e.graph->Colors[0];
		int v2 = -1, c2 = -1;
		
		//N1

		//If n1 changes are possible
		if (lowIndex < highIndex) {
			//For each vertex in graph
			for (int v = 0; v < e.graph->Size(); v++) {
				int vc = e.graph->Colors[v]; //current vertex color
				//If conflict and high index (can be changed)
				if (evaluationMatrix[v][vc] > 0 && colorHistogram[vc] == highIndex) {
					//For each avalible color
					for (int c = 0; c < colorCount; c++) {
						//If low index (can be increased)
						if (colorHistogram[c] == lowIndex) {
							//delta f
							int df = evaluationMatrix[v][c] - evaluationMatrix[v][vc];
							//if best or good and allowed by taboo list 
							if (df < min_df || (tabooList[v][c] < mt && df == min_df)) {
								//replace best values
								min_df = df;
								v1 = v;
								c1 = c;
							}
						}
					}
				}
			}
		}
		

		//N2

		//For each vertex in graph
		for (int v = 0; v < e.graph->Size(); v++) {
			int vc = e.graph->Colors[v]; //current vertex color
			//If conflict
			if (evaluationMatrix[v][vc] > 0) {
				//For each other vertex in graph
				for (int u = 0; u < e.graph->Size(); u++) {
					int uc = e.graph->Colors[u]; //current vertex color
					//If not same vertex
					if (v != u) {
						//delta f
						int df = (evaluationMatrix[v][uc] - evaluationMatrix[v][vc])+(evaluationMatrix[u][vc] - evaluationMatrix[u][uc]) - 2 * (e.graph->IsEdge(v, u));
						//if best or good and allowed by taboo list and 
						if (df <= min_df || (df == min_df && tabooList[v][uc] < mt && tabooList[u][vc] < mt)) {
							//replace best values
							min_df = df;
							v1 = v;
							v2 = u;
							c1 = uc;
							c2 = vc;
						}
					}
				}
			}
		}

		return move{ min_df, v1, v2, c1, c2 };
	}
	
	void BitsColoringAlgorithm::TabooSearch::Search(int alpha)
	{
		//best solution
		std::vector<int> sb = e.graph->Colors;
		//iterations since sb updated
		int d = 0;
		//evaluation function output of the current and best solution
		int fs = EvaluationFunction();

		for (int i = 0; d < alpha && fs>0; i++) {
			//best move
			move bm = ExploreNeighborhood(i-10); // TODO: improve tabu tenure
			
			ExecuteMove(bm);

			if (bm.df < 0) {
				sb = e.graph->Colors;
				d = 0;
				fs -= bm.df;
			}
			else {
				d++;
			}
		}

		e.graph->Colors = sb;
	}
}


