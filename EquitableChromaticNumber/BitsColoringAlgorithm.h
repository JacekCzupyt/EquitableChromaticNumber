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
			
			BitsColoringAlgorithm& e;
			std::vector<std::vector<int>> evaluationMatrix;
			std::vector<std::vector<int>> tabooList;

			std::vector<std::vector<int>> ConstructEvaluationMatrix();
			std::vector<std::vector<int>> InitializeTabooList();
			void ExploreNeighborhood();
		};
	};
}



