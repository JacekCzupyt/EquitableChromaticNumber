#include "BitsColoringAlgorithm.h"
#include <random>
#include <chrono>

namespace ecnGraph {

	struct timer {
	private:
		std::chrono::steady_clock::time_point TickTime;
		bool started = false;
		long long totalTime = 0;
	public:
		void tick() {
			if (started == true)
				throw 400;
			TickTime = std::chrono::steady_clock::now();
			started = true;
		}

		void tock() {
			if (started == false)
				throw 400;
			totalTime += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - TickTime).count();
			started = false;
		}

		double time() { return (double)totalTime / 1e6; }
	};


	BitsColoringAlgorithm::BitsColoringAlgorithm(double _duration)
	{
		duration = _duration;
	}

	int ecnGraph::BitsColoringAlgorithm::Color(ColoredGraph& _graph)
	{
		graph = &_graph;

		//exception for a graph with no edges
		if (graph->Deg() == 0) {
			for (int i = 0; i < graph->Size(); i++) {
				graph->Colors[i] = 0;
			}
			return 1;
		}

		TabooSearch taboo(*this);
		int BestColorCount = taboo.InitialBinarySearch(Alpha0);
		std::vector<int> BestColoring = graph->Colors;

		int colorCount = BestColorCount;
		auto startTime = std::chrono::steady_clock::now();

		while (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startTime).count() < duration * 1e6) {
			
			if (BestColorCount == 2)
				break;

			if (colorCount <= BestColorCount - m || colorCount == 2)
				colorCount = BestColorCount - 1;
			else
				colorCount--;

			if (taboo.IteratedSearch(colorCount, Beta, Alpha) == 0) {
				BestColorCount = colorCount;
				BestColoring = graph->Colors;
			}
		}

		graph->Colors = BestColoring;
		return BestColorCount;
	}

	int BitsColoringAlgorithm::TabooSearch::InitialBinarySearch(int alpha)
	{
		// Algorithm presented in the paper suggested u = |V|, which I believe is wrong
		int l = 0, u = e.graph->Size() + 1;
		std::vector<int> BestColoring;
		
		int BestColorcount = u;

		// Algorithm presented in the paper suggested u > l + 1, which I believe is wrong
		while (u > l) {
			int k = (u + l) / 2;
			colorCount = k;
			InitializeKColoring();
			if (Search(alpha) == 0) {
				BestColorcount = k;
				BestColoring = e.graph->Colors;
				u = k;
			}
			else
				// Algorithm presented in the paper suggested l = k, which I believe is wrong
				l = k + 1;
		}

		e.graph->Colors = BestColoring;
		return BestColorcount;
	}

	BitsColoringAlgorithm::TabooSearch::TabooSearch(BitsColoringAlgorithm& _e) : e(_e), colorCount(-1) {
		ConstructStructures();
	}

	void BitsColoringAlgorithm::TabooSearch::InitializeEvaluationMatrix()
	{
		for (int i = 0; i < e.graph->Size(); i++) {
			for (int c = 0; c < colorCount; c++) {
				evaluationMatrix[i][c] = 0;
			}
			for (int j : e.graph->GetNeighbours(i)) {
				evaluationMatrix[i][e.graph->Colors[j]]++;
			}
		}
	}

	void BitsColoringAlgorithm::TabooSearch::InitializeTabooList()
	{
		for (int i = 0; i < e.graph->Size(); i++) {
			for (int c = 0; c < colorCount; c++) {
				tabooList[i][c] = INT_MIN;
			}
		}
	}

	void BitsColoringAlgorithm::TabooSearch::InitializeColorHistogram()
	{
		for (int c = 0; c < colorCount; c++) {
			colorHistogram[c] = 0;
		}
		for (int i = 0; i < e.graph->Size(); i++) {
			colorHistogram[e.graph->Colors[i]]++;
		}
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
		int lowIndex = e.graph->Size() / colorCount;
		int highIndex = lowIndex + (e.graph->Size() % colorCount == 0);

		std::vector<move> BestMoves;
		BestMoves.reserve(e.graph->Size() * (e.graph->Size() + colorCount));
		BestMoves.push_back(move{ 0, 0, e.graph->Colors[0], -1, -1 });
		int min_df = 0;
		
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
					//If not same color (includes if not same vertex)
					if (vc != uc) {
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

		// Initialize and randomize vertex list (Fisher�Yates shuffle)
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

		// assign colors to the remaining verticies
		// TODO_ADDRESSED: test, I'd be surprised if this does not have bugs
		// PS. I was right
		std::vector<int> minSet;
		minSet.reserve(e.graph->Size() - i);
		int minVal = INT_MAX;
		for (; i < e.graph->Size(); i++) {
			minSet.clear();
			minVal = INT_MAX;
			int c = i % colorCount;
			for (int v = 0; v < e.graph->Size(); v++) {
				if (colors[v] == -1) {
					int val = std::count_if(e.graph->GetNeighbours(v).begin(), e.graph->GetNeighbours(v).end(), [colors, c](int u) {return colors[u] == c; });
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

		RefreshStructures();
	}

	void BitsColoringAlgorithm::TabooSearch::DirectedPertubation(int eta, int fs)
	{
		//directed pertubations

		for (int i = 0; i < eta; i++) {
			//best move
			move bm = ExploreNeighborhood(i - 2000 - (rand()%1000));

			ExecuteMove(bm, i);
		}
	}

	void BitsColoringAlgorithm::TabooSearch::RandomPertubation(int eta)
	{
		//random pertubations
		for (int i = 0; i < eta; i++) {
			int v, u;
			do {
				v = rand() % e.graph->Size();
				u = rand() % e.graph->Size();
			} while (e.graph->Colors[v] == e.graph->Colors[u]);
			std::swap(e.graph->Colors[v], e.graph->Colors[u]);
		}
		RefreshStructures();
	}

	void BitsColoringAlgorithm::TabooSearch::PertubationOperator(int eta1, int eta2, float p, int fs)
	{
		if ((float)rand() / RAND_MAX < p) {
			RandomPertubation(eta2);
		}
		else {
			DirectedPertubation(eta1, fs);
		}
	}
	
	int BitsColoringAlgorithm::TabooSearch::Search(int alpha)
	{
		//best solution
		std::vector<int> sb = e.graph->Colors;
		//iterations since sb updated
		int d = 0;
		//evaluation function output of the current and best solution
		int fs = EvaluationFunction();

		for (int i = 0; d < alpha && fs>0; i++) {
			//best move
			move bm = ExploreNeighborhood(i-5-(rand()%5)); // TODO: implement other tabu tenure rules?
			
			ExecuteMove(bm, i);

			if (bm.df < 0) {
				sb = e.graph->Colors;
				d = 0;
				fs += bm.df;
			}
			else {
				d++;
			}
		}

		e.graph->Colors = sb;
		RefreshStructures();
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
			PertubationOperator(e.ETA1, (int)(e.ETA2*e.graph->Size()), e.P, fs);
			int fsp = Search(alpha);

			if (fsp < fs) {
				s = e.graph->Colors;
				d = 0;
				fs = fsp;
			}
			else {
				e.graph->Colors = s;
				RefreshStructures();
				d++;
			}
		}

		e.graph->Colors = s;
		return fs;
	}

	void BitsColoringAlgorithm::TabooSearch::ConstructStructures()
	{
		evaluationMatrix = std::vector<std::vector<int>>(e.graph->Size(), std::vector<int>(e.graph->Size(), 0));
		tabooList = std::vector<std::vector<int>>(e.graph->Size(), std::vector<int>(e.graph->Size(), INT_MIN));
		colorHistogram = std::vector<int>(e.graph->Size(), 0);
	}

	void BitsColoringAlgorithm::TabooSearch::RefreshStructures()
	{
		InitializeEvaluationMatrix();
		InitializeTabooList();
		InitializeColorHistogram();
	}
}


