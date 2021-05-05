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
			
			
		private:

			struct move { int df, v1, v2, c1, c2; };
			
			BitsColoringAlgorithm& e;
			std::vector<std::vector<int>> evaluationMatrix;
			std::vector<std::vector<int>> tabooList;
			std::vector<int> colorHistogram;

			std::vector<std::vector<int>> ConstructEvaluationMatrix();
			std::vector<std::vector<int>> InitializeTabooList();
			std::vector<int> InitializeColorHistogram();

			/// <summary>
			/// Explores neighborhood of current coloring, does not change the graph
			/// </summary>
			/// <param name="mt">Maxiumum time allowed by tabu search (t - tt)</param>
			/// <returns>The best avalible move</returns>
			move ExploreNeighborhood(int mt);

			/// <summary>
			/// Runs a tabu search on the current coloring of the graph
			/// </summary>
			/// <param name="alpha">Depth of the tabu serch</param>
			void Search(int alpha);
			
		};
	};
}



