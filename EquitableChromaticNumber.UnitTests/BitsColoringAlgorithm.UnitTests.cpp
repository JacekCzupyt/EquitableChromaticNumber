#include "pch.h"
#include "CppUnitTest.h"
#include "../EquitableChromaticNumber/BitsColoringAlgorithm.h"
#include "../EquitableChromaticNumber/BitsColoringAlgorithm.cpp"
#include "../EquitableChromaticNumber/ColoredGraph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EquitableChromaticNumberUnitTests {
	using namespace ecnGraph;

	TEST_CLASS(BitsColoringAlgorithmUnitTests) {
	public:
		TEST_METHOD(IsColoredSmallGraphs) {
			BitsColoringAlgorithm Bits(0.01f);
			srand(0);
			for (int i = 0; i < 100; i++) {
				ColoredGraph g = GenerateRandomGraph(5 + i % 10, (double)rand()/RAND_MAX);
				Bits.Color(g);
				Assert::IsTrue(g.IsColored());
			}
		}

	private:
		ColoredGraph GenerateRandomGraph(int n, double density) {
			ColoredGraph graph(n);
			for (int i = 0; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
					if ((double)rand() / RAND_MAX < density) {
						graph.AddEdge(i, j);
					}
				}
			}
			return graph;
		}
	};
}