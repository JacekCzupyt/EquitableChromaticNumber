#include "BitsColoringAlgorithm.h"
#include <random>

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

	void BitsColoringAlgorithm::TabooSearch::ExecuteMove(move m, int t)
	{
		PartialExecuteMove(m.v1, m.c1, t);
		PartialExecuteMove(m.v2, m.c2, t);
	}

	void BitsColoringAlgorithm::TabooSearch::PartialExecuteMove(int v, int c, int t)
	{
		if (v == -1) return;
		//previous color
		int pc = e.graph->Colors[v];

		//update histogram
		colorHistogram[pc]--;
		colorHistogram[c]++;
		//update tabu list
		tabooList[v][pc] = t;
		//update evaluation matrix
		for (int u : e.graph->GetNeighbours(v)) {
			evaluationMatrix[u][pc]--;
			evaluationMatrix[u][c]++;
		}
		//update graph
		e.graph->Colors[v] = c;
	}
	
	BitsColoringAlgorithm::TabooSearch::move BitsColoringAlgorithm::TabooSearch::ExploreNeighborhood(int mt)
	{
		// TODO: replace GetColorCount with preexisting variable
		int colorCount = e.graph->GetColorCount();
		int lowIndex = e.graph->Size() / colorCount;
		int highIndex = lowIndex + (e.graph->Size() % colorCount == 0);

		std::vector<move> BestMoves;
		BestMoves.reserve(e.graph->Size() * (e.graph->Size() + colorCount));
		BestMoves.push_back(move{ 0, 0, e.graph->Colors[0], -1, -1 });
		int min_df = 0;
		//int v1 = 0, c1 = e.graph->Colors[0];
		//int v2 = -1, c2 = -1;
		
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
							//if best 
							if (df < min_df) {
								min_df = df;
								BestMoves.clear();
								BestMoves.push_back(move{ df, v, c, -1, -1 });
							}// or good and allowed by taboo list
							else if (tabooList[v][c] < mt && df == min_df) {
								BestMoves.push_back(move{ df, v, c, -1, -1 });
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
						//if best
						if (df < min_df) {
							min_df = df;
							BestMoves.clear();
							BestMoves.push_back(move{ df, v, uc, u, vc });
						}// or good and allowed by taboo list
						else if (df == min_df && tabooList[v][uc] < mt && tabooList[u][vc] < mt) {
							BestMoves.push_back(move{ df, v, uc, u, vc });
						}
					}
				}
			}
		}

		return BestMoves[rand() % BestMoves.size()];
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
			
			ExecuteMove(bm, i);

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
	
	void BitsColoringAlgorithm::TabooSearch::Refresh()
	{
		ConstructEvaluationMatrix();
		InitializeTabooList();
		InitializeColorHistogram();
	}
}


