#pragma once
#include "AbstractColoringAlgorithm.h"

namespace ecnGraph {
	class BitsColoringAlgorithm :
		public AbstractColoringAlgorithm
	{
	public:
		BitsColoringAlgorithm(double _duration);

		virtual int Color(ColoredGraph& _graph) override;

	private:
		double duration;
		ColoredGraph * graph;
		

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
			/// /// <returns>The evaluation of the provided solution</returns>
			int IteratedSearch(int k, int beta, int alpha);

			void Refresh();
		private:
			int colorCount;

			struct move { int df, v1, v2, c1, c2; };
			
			BitsColoringAlgorithm& e;
			std::vector<std::vector<int>> evaluationMatrix;
			std::vector<std::vector<int>> tabooList;
			std::vector<int> colorHistogram;

			std::vector<std::vector<int>> ConstructEvaluationMatrix();
			std::vector<std::vector<int>> InitializeTabooList();
			std::vector<int> InitializeColorHistogram();
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

			void PertubationOperator();
		};
	};
}



