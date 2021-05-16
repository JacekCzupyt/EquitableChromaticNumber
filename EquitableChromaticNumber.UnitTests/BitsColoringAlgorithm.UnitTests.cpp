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
			BitsColoringAlgorithm Bits(0.2f);
			srand(0);
			for (int i = 0; i < 10; i++) {
				ColoredGraph g = GenerateRandomGraph(5 + i % 10, (double)rand()/RAND_MAX);
				int res = Bits.Color(g);
				Logger::WriteMessage((std::to_string(res) + "\n").c_str());
				Assert::IsTrue(g.IsColored());
			}
		}

		TEST_METHOD(IsColoredBigGraphs) {
			BitsColoringAlgorithm Bits(5.0f);
			srand(0);
			ColoredGraph g = GenerateRandomGraph(100, 0.15f);
			int res = Bits.Color(g);
			Logger::WriteMessage((std::to_string(res) + "\n").c_str());
			Assert::IsTrue(g.IsColored());
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