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

		std::vector<std::vector<int>> tabooList;

		std::vector<std::vector<int>> ConstructEvaluationMatrix();
		

		class ExploreNeighborhood {
		public:
			void Explore();
			ExploreNeighborhood();
			std::vector<std::vector<int>> evaluationMatrix;
		};
	};
}



