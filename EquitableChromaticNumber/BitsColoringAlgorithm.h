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
	};
}



