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
		auto matrix = std::vector<std::vector<int>>(e.graph->Size(), std::vector<int>(colorCount, 0));
		for (int i = 0; i < e.graph->Size(); i++) {
			for (int j : e.graph->GetNeighbours(i)) {
				matrix[i][j]++;
			}
		}
		return matrix;
	}

	std::vector<std::vector<int>> BitsColoringAlgorithm::TabooSearch::InitializeTabooList()
	{
		return std::vector<std::vector<int>>(e.graph->Size(), std::vector<int>(colorCount, INT_MIN));
	}

	std::vector<int> BitsColoringAlgorithm::TabooSearch::InitializeColorHistogram()
	{
		auto hist = std::vector<int>(colorCount, 0);
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
		int colorCount = colorCount;
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

	void BitsColoringAlgorithm::TabooSearch::InitializeKColoring()
	{
		std::vector<int>& colors = e.graph->Colors;

		// Initialize and randomize vertex list (Fisher–Yates shuffle)
		std::vector<int> vert(e.graph->Size());
		for (int i = 0; i < e.graph->Size(); i++) {
			vert[i] = i;
			colors[i] = -1;
		}
			
		for (int i = e.graph->Size() - 1; i > 0; i--)
			std::swap(vert[i], vert[rand() % (i + 1)]);

		//color initial k verticies (k - color count)
		int i;
		for (i = 0; i < colorCount; i++) {
			colors[vert[i]] = i;
		}

		//assign colors to the remaining verticies
		// TODO: test, I'd be surprised if this does not have bugs
		std::vector<int> minSet;
		minSet.reserve(e.graph->Size() - i);
		int minVal = INT_MAX;
		for (; i < e.graph->Size(); i++) {
			minSet.clear();
			minVal = INT_MAX;
			int c = i % colorCount;
			for (int v = 0; v < e.graph->Size(); v++) {
				if (colors[v] != -1) {
					int val = std::count_if(e.graph->GetNeighbours(v).begin(), e.graph->GetNeighbours(v).end(), [colors, c](int u) {colors[u] == c; });
					if (val < minVal) {
						minSet.clear();
						minVal = val;
					}
					if (val == minVal) {
						minSet.push_back(v);
					}
						
				}
			}
			colors[minSet[rand() % minSet.size()]] = c;
		}
	}

	void BitsColoringAlgorithm::TabooSearch::DirectedPertubation(int eta)
	{
		//directed pertubations
		//evaluation function output of the current and best solution
		// TODO: Get precomputed evaluation function?
		int fs = EvaluationFunction();

		for (int i = 0; i < eta; i++) {
			//best move
			move bm = ExploreNeighborhood(i - 2000); // TODO: improve tabu tenure

			ExecuteMove(bm, i);
		}
	}

	void BitsColoringAlgorithm::TabooSearch::RandomPertubation(int eta)
	{
		//random pertubations
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
						int df = (evaluationMatrix[v][uc] - evaluationMatrix[v][vc]) + (evaluationMatrix[u][vc] - evaluationMatrix[u][uc]) - 2 * (e.graph->IsEdge(v, u));
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
	}

	void BitsColoringAlgorithm::TabooSearch::PertubationOperator(int eta1, int eta2, float p)
	{
		if ((float)rand() / RAND_MAX < p) {
			RandomPertubation(eta2);
		}
		else {
			DirectedPertubation(eta1);
		}
	}
	
	int BitsColoringAlgorithm::TabooSearch::Search(int alpha)
	{
		//best solution
		std::vector<int> sb = e.graph->Colors;
		//iterations since sb updated
		int d = 0;
		//evaluation function output of the current and best solution
		// TODO: Get precomputed evaluation function?
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
		return fs;
	}
	
	int BitsColoringAlgorithm::TabooSearch::IteratedSearch(int k, int beta, int alpha)
	{
		colorCount = k;
		InitializeKColoring();
		Search(alpha);
		
		// Current best solution
		std::vector<int> s = e.graph->Colors;
		// Iterations since s has been updated
		int d = 0;
		// Evaluation of the current solution
		int fs = EvaluationFunction();

		while (d < beta && fs > 0) {
			PertubationOperator();
			int fsp = Search(alpha);

			if (fsp < fs) {
				s = e.graph->Colors;
				d = 0;
				fs = fsp;
			}
			else {
				e.graph->Colors = s;
				d++;
			}
		}

		e.graph->Colors = s;
		return fs;
	}

	void BitsColoringAlgorithm::TabooSearch::Refresh()
	{
		ConstructEvaluationMatrix();
		InitializeTabooList();
		InitializeColorHistogram();
	}
}


