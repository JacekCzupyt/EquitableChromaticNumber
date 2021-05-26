#include "pch.h"
#include "CppUnitTest.h"
#include "../EquitableChromaticNumber/JfkAlgorithm.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EquitableChromaticNumberUnitTests {
	using namespace ecnGraph;

	TEST_CLASS(JfkAlgorithmUnitTests) {
public:
	TEST_METHOD(IsColoredSmallGraphs) {
		JfkAlgorithm jfk;
		srand(0);
		int seed = rand();
		for (int i = 0; i < 10; i++) {
			srand(seed);
			seed = rand();
			ColoredGraph g = GenerateRandomGraph(5 + i % 10, /*0.3f + 0.7f **/ (double)rand() / RAND_MAX);
			int res = jfk.Color(g);
			Logger::WriteMessage((std::to_string(res) + "\n").c_str());
			Assert::IsTrue(g.IsColored(), L"Falied to color");
			Assert::IsTrue(res = g.GetColorCount(), L"Result inconsistent with graph color count");
		}
	}

	TEST_METHOD(IsColoredBigGraphs) {
		JfkAlgorithm jfk;
		srand(0);
		ColoredGraph g = GenerateRandomGraph(100, 0.15f);
		int res = jfk.Color(g);
		Logger::WriteMessage((std::to_string(res) + "\n").c_str());
		Assert::IsTrue(g.IsColored(), L"Falied to color");
		Assert::IsTrue(res = g.GetColorCount(), L"Result inconsistent with graph color count");
		Assert::IsTrue(res < 25, L"Res seems too high, but check in with me if unsure");
	}

	TEST_METHOD(Color_myciel7) {
		JfkAlgorithm jfk;
		ColoredGraph g = ReadColFile("../TestCases/myciel7.col");
		srand(0);
		int res = jfk.Color(g);
		Logger::WriteMessage((std::to_string(res) + "\n").c_str());
		Assert::IsTrue(g.IsColored(), L"Falied to color");
		Assert::IsTrue(res = g.GetColorCount(), L"Result inconsistent with graph color count");
		Assert::IsTrue(res < 30, L"Res seems too high, but check in with me if unsure");
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