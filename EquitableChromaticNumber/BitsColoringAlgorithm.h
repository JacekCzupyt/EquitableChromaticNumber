#pragma once
#include "AbstractColoringAlgorithm.h"

namespace ecnGraph {
	class BitsColoringAlgorithm :
		public AbstractColoringAlgorithm
	{
	public:
		BitsColoringAlgorithm(double _duration);

		virtual int Color(ColoredGraph& _graph) override;

		const int ETA1 = (int)5e2;//paper suggests 5e3
		const float ETA2 = 0.3f;
		const float P = 0.7f;
		const int Alpha0 = (int)1e2;
		const int Alpha = (int)1e2;//paper suggests 1e5
		const int m = 4;
		const int Beta = 10;//paper suggests 30

	private:
		double duration;
		ColoredGraph * graph = nullptr;
		

		class TabooSearch {
		public:
			TabooSearch(BitsColoringAlgorithm& _e);
			
			/// <summary>
			/// Runs a tabu search on the current coloring of the graph
			/// </summary>
			/// <param name="alpha">Depth of the tabu serch</param>
			/// <returns>The evaluation of the provided solution</returns>
			int Search(int alpha);

			/// <summary>
			/// Runs an iterated tabu search on the provided graph with the specified color count
			/// </summary>
			/// <param name="k">Color count</param>
			/// <param name="beta">Depth of the iterated tabu serch</param>
			/// <param name="alpha">Depth of the tabu serch</param>
			/// <returns>The evaluation of the provided solution</returns>
			int IteratedSearch(int k, int beta, int alpha);

			/// <summary>
			/// Preforms a binary search to find an appropiate inital color count
			/// </summary>
			/// <param name="alpha">Depth of the tabu search</param>
			/// <returns>Appropiate inital color count</returns>
			int InitialBinarySearch(int alpha);

		private:
			int colorCount;

			void ConstructStructures();
			void RefreshStructures();

			struct move { int df, v1, c1, v2, c2; };
			
			BitsColoringAlgorithm& e;
			std::vector<std::vector<int>> evaluationMatrix;
			std::vector<std::vector<int>> tabooList;
			std::vector<int> colorHistogram;

			void InitializeEvaluationMatrix();
			void InitializeTabooList();
			void InitializeColorHistogram();
			int EvaluationFunction(const std::vector<int>& colors);
			int EvaluationFunction();

			/// <summary>
			/// Updates the graph color vector, evaluation matrix, taboo list and color histogram
			/// </summary>
			void ExecuteMove(move m, int t);
			void PartialExecuteMove(int v, int c, int t);

			/// <summary>
			/// Explores neighborhood of current coloring, does not change the graph
			/// </summary>
			/// <param name="mt">Maxiumum time allowed by tabu search (t - tt)</param>
			/// <returns>The best avalible move</returns>
			move ExploreNeighborhood(int mt);

			/// <summary>
			/// Generate an initial solution with as few conflicts as possible
			/// </summary>
			void InitializeKColoring();

			void PertubationOperator(int eta1, int eta2, float p, int fs);
			void DirectedPertubation(int eta1, int fs);
			void RandomPertubation(int eta1);
		};
	};
}



